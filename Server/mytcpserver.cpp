#include "mytcpserver.h"


MyTcpServer::MyTcpServer(QObject *parent, int port) : QObject(parent)
{
	mTcpServer = new QTcpServer(this);

	connect(mTcpServer, &QTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);

    mTcpServer->listen(QHostAddress::Any, port);

    qDebug() << "Server is started. It is listening your...";

	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("../history.db3");
	db.open();
}

MyTcpServer::~MyTcpServer()
{
	db.close();

    for (QHash<QString, QTcpSocket*>::iterator allClients = clients.begin(); allClients != clients.end(); allClients++)
    {
       clients.take(allClients.key())->close();
    }

}

void MyTcpServer::slotNewConnection() // клиент подключился
{
	QTcpSocket* mTcpSocket = mTcpServer->nextPendingConnection();   //  его слот

	connect(mTcpSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotRead); // возможность отловить сообщения от клиента
	connect(mTcpSocket, &QTcpSocket::disconnected, this, &MyTcpServer::clientDisconnected); // клиент отключился
}

void MyTcpServer::clientDisconnected()
{
    QHash<QString, QTcpSocket*>::iterator client = nameClient((QTcpSocket*)sender());
    QString key = client.key();
    clients.erase(client);  // удаляем запись из хэш-таблицы

    for (QHash<QString, QTcpSocket*>::iterator allClients = clients.begin(); allClients != clients.end(); allClients++)
    {
        sendString(allClients.value(), key, DEL_INTERLOCUTOR);  // удаляем у всех клиентов иконку отключенного
    }
}

void MyTcpServer::sendString(QTcpSocket* clientReceiver, const QString& str, int type)    // отправить сообщение клиенту
{
	if (clientReceiver == 0)
		return;

	QByteArray block;
	QDataStream stream(&block, QIODevice::ReadWrite);

    stream << quint16(0) << quint16(0) << str;
    stream.device()->seek(0);
    stream << (quint16)(type) << (quint16)(block.size() - 2 * sizeof(quint16)); // отправляем тип, размер сообщения

	clientReceiver->write(block);
}

void MyTcpServer::slotRead() // считать сообщение от клиента
{
	QTcpSocket* pClientSocket = (QTcpSocket*)sender();

	QDataStream stream(pClientSocket);

	qint16 type;
	stream >> type;     // определяем тип сообщения
    qDebug() << "pClientSocket->bytesAvailable():"<<pClientSocket->bytesAvailable();

    if (type == MESSAGE_FILE)
    {
		QHash<QString, QTcpSocket*>::iterator client = nameClient(pClientSocket);
		QString name = client.key();
		if (pClientSocket != interlocutors.value(name))
            sendFile(stream, interlocutors.value(name));
		return;
	}

	QSqlQuery query;
	query.prepare("INSERT INTO message (id, user_to, user_from, message_text) VALUES (NULL, ?, ?, ?)");

	QString buff;
	qint16 m_msgSize = -1;

	while (true)
	{
		if (m_msgSize < 0)
		{
			if (pClientSocket->bytesAvailable() < sizeof(int))
				return;

			stream >> m_msgSize;   // считали размер сообщения (2 байта)
		}

		else
		{
			if (pClientSocket->bytesAvailable() < m_msgSize)
				return;

			stream >> buff;

            if (type == MESSAGE_TEXT_TO) // отправка сообщения
			{
				QHash<QString, QTcpSocket*>::iterator client = nameClient(pClientSocket);
				QString name = client.key();    // имя отправителя


				QHash<QString, QTcpSocket*>::iterator client1 = nameClient(interlocutors.value(name));
                QString nameRec = client1.key(); // имя получателя


                if (pClientSocket == interlocutors.value(nameRec))
                    sendString(interlocutors.value(name), buff, MESSAGE_TEXT_FROM); // сообщение в чате от собеседника

                sendString(pClientSocket, buff, MESSAGE_TEXT_TO); // сообщение в чате от себя

                query.addBindValue(name);
                query.addBindValue(nameRec);
				query.addBindValue(buff);
				query.exec();
			}

            else if (type == NAME_CLIENT) // отправка своего имени
				addClient(pClientSocket, buff);

            else if (type == NAME_INTERLOCUTOR) // отправка имени собеседника
				whomToSend(pClientSocket, buff);

			m_msgSize = -1;
		}
	}
}

void MyTcpServer::addClient(QTcpSocket* pClientSocket, QString buff)
{
	showAllClients(pClientSocket, buff); // добавить иконки клиентам

	clients.insert(buff, pClientSocket); // добавить запись о клиенте
}

void MyTcpServer::whomToSend(QTcpSocket* pClientSocket, QString name) // смена собеседника
{
	QHash<QString, QTcpSocket*>::iterator client = nameClient(pClientSocket);
	QString whoWrite = client.key();    // имя отправителя

	QTcpSocket* whoRead = clients.value(name);  // сокет получателя

	// запоминаем какому сокету пишет клиент
	if (interlocutors.contains(whoWrite) == true)
		interlocutors[whoWrite] = whoRead;
	else
		interlocutors.insert(whoWrite, whoRead);


	// метод отсылающий клиенту историю сообщений с новым собеседником
	sendHistory(pClientSocket, clients.value(name)); // сокет клиента отправителя, сокет получателя
}

void MyTcpServer::sendHistory(QTcpSocket* clientSender, QTcpSocket* clientReceiver)
{
	QVector<QString> chat;   // весь чат. один элемент вектора - одно сообщение (отправителя/получателя)
	QVector<QDateTime> time; // время сообщения
	QVector<bool> initiator; // это сообщение отправителя(false) или получателя(true)

	QHash<QString, QTcpSocket*>::iterator client1 = nameClient(clientSender);
	QString name1 = client1.key();
	QHash<QString, QTcpSocket*>::iterator client2 = nameClient(clientReceiver);
	QString name2 = client2.key();

	QSqlQuery query;
	query.prepare("SELECT id, user_to, user_from, message_text FROM message WHERE user_to = ? AND user_from = ? OR user_from = ? AND user_to = ?");
	query.addBindValue(name1);
	query.addBindValue(name2);
	query.addBindValue(name1);
	query.addBindValue(name2);
	query.exec();

	while (query.next())
	{
		QString to = query.value(1).toString();
		QString m_text = query.value(3).toString();
		chat.append(m_text);
		time.push_back(QDateTime::currentDateTime());
		if (to == name1)
			initiator.push_back(true);
		else
			initiator.push_back(false);
	}

    sendString(clientSender, "", SEVERAL_MESSAGES);
	for (size_t i = 0; i < chat.size(); i++)
    {
        if ( initiator[i] == true)
            sendString(clientSender, chat[i], MESSAGE_TEXT_FROM);
        else
            sendString(clientSender, chat[i], MESSAGE_TEXT_TO);
	}
}

void MyTcpServer::showAllClients(QTcpSocket* pClientSocket, QString buff)
{
	// пробегаемся по каждому клиенту
    sendString(pClientSocket, "", SEVERAL_MESSAGES);
	for (QHash<QString, QTcpSocket*>::iterator allClients = clients.begin(); allClients != clients.end(); allClients++)
	{
		// новому клиенту необходимо отобразить весь список собеседников
        sendString(pClientSocket, allClients.key(), NAME_CLIENT);
		// каждому старому клиенту добавляем нового собеседника
        sendString(allClients.value(), buff, NAME_CLIENT);
	}
}

void MyTcpServer::sendFile(QDataStream& stream, QTcpSocket* clientReceiver)
{
    qDebug() <<"here";
	QByteArray block_to;
    QDataStream stream_to(&block_to, QIODevice::ReadWrite);

    stream_to << quint16(MESSAGE_FILE); // type

    qint32 totalSize;
    stream >> totalSize;
    stream_to << totalSize;  // size
    qDebug() << "sendFile(server):"<<totalSize;

    QString nameFile;
    stream >> nameFile;
    stream_to << nameFile;  // name of file
    qDebug() << "sendFile(server):"<<nameFile;


    qint32 sizeSendData = 0;
    char block[4*1024];
    qint32 toFile;
    forever
    {
		stream >> toFile;
        qDebug() << "sendFile(server):"<< toFile;
		stream_to << toFile;
        stream.readRawData(block, toFile);
        stream_to.writeRawData(block, toFile);
        sizeSendData += toFile;
        qDebug() << sizeSendData;
        clientReceiver->write(block_to);
        if (sizeSendData == totalSize || toFile == 0)
        {			         
			return;
		}
    }
}


QHash<QString, QTcpSocket*>::iterator MyTcpServer::nameClient(QTcpSocket* client)   // запись таблицы клиента с сокетом client
{
    for (QHash<QString, QTcpSocket*>::iterator allClients = clients.begin(); allClients != clients.end(); allClients++)
        if (allClients.value() == client)   // нашли клиента
            return allClients;
}
