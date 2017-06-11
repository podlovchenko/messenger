#include "serversocket.h"

ServerSocket::ServerSocket(QObject *parent) : QObject(parent), db("../history.db3")
{    
}

ServerSocket::~ServerSocket()
{
    for (QHash<QString, QTcpSocket*>::iterator allClients = clients.begin(); allClients != clients.end(); allClients++)
    {
       clients.take(allClients.key())->close();
    }

}

void ServerSocket::connectSignals(QTcpSocket* mTcpSocket) // клиент подключился
{
    connect(mTcpSocket, &QTcpSocket::readyRead, this, &ServerSocket::slotRead); // возможность отловить сообщения от клиента   
    connect(mTcpSocket, &QTcpSocket::disconnected, this, &ServerSocket::clientDisconnected); // клиент отключился
}

void ServerSocket::clientDisconnected()
{
    QHash<QString, QTcpSocket*>::iterator client = nameClient((QTcpSocket*)sender());
    QString key = client.key();
    clients.erase(client);  // удаляем запись из хэш-таблицы

    for (QHash<QString, QTcpSocket*>::iterator allClients = clients.begin(); allClients != clients.end(); allClients++)
    {
        sendString(allClients.value(), key, DEL_INTERLOCUTOR);  // удаляем у всех клиентов иконку отключенного
    }
}

void ServerSocket::sendString(QTcpSocket* clientReceiver, const QString& str, int type)    // отправить сообщение клиенту
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

void ServerSocket::slotRead() // считать сообщение от клиента
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();

    QDataStream stream(pClientSocket);

    qint16 type;
    stream >> type;     // определяем тип сообщения

    if (type == MESSAGE_FILE)
    {
        QHash<QString, QTcpSocket*>::iterator client = nameClient(pClientSocket);
        QString name = client.key();

        QHash<QString, QTcpSocket*>::iterator client1 = nameClient(interlocutors.value(name));
        QString nameRec = client1.key(); // имя получателя

        QString nameFile;
        if (pClientSocket != interlocutors.value(name))
            nameFile = saveFile(stream, pClientSocket);

        db.insert(TYPE_FILE, name, nameRec, nameFile);

        sendFile(interlocutors.value(name), nameFile);

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

                db.insert(TYPE_TEXT, name, nameRec, buff);
            }

            else if (type == NAME_CLIENT) // отправка своего имени
                addClient(pClientSocket, buff);

            else if (type == NAME_INTERLOCUTOR) // отправка имени собеседника
                whomToSend(pClientSocket, buff);

            m_msgSize = -1;
        }
    }
}

void ServerSocket::addClient(QTcpSocket* pClientSocket, QString buff)
{
    showAllClients(pClientSocket, buff); // добавить иконки клиентам

    clients.insert(buff, pClientSocket); // добавить запись о клиенте
}

void ServerSocket::whomToSend(QTcpSocket* pClientSocket, QString name) // смена собеседника
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

void ServerSocket::sendHistory(QTcpSocket* clientSender, QTcpSocket* clientReceiver)
{
    QHash<QString, QTcpSocket*>::iterator client1 = nameClient(clientSender);
    QString name1 = client1.key();
    QHash<QString, QTcpSocket*>::iterator client2 = nameClient(clientReceiver);
    QString name2 = client2.key();

    QVector<QPair<QString, bool> > history = db.getHistory(name1, name2);

    sendString(clientSender, "", SEVERAL_MESSAGES);

    QVector<QPair<QString, bool> >::const_iterator i = history.constBegin();
    while(i != history.constEnd())
    {
        if (i->second == true)
            sendString(clientSender, i->first, MESSAGE_TEXT_FROM);
        else
            sendString(clientSender, i->first, MESSAGE_TEXT_TO);
        i++;
    }
}

void ServerSocket::showAllClients(QTcpSocket* pClientSocket, QString buff)
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

QString ServerSocket::saveFile(QDataStream& stream, QTcpSocket* pClientSocket)
{
    quint64 lBytesDone = 0;
    quint64 lSize = 0;
    quint64 lBytes = 0;
    QString nameFile;

    stream >> lSize >> nameFile;

    QFile* file = new QFile(pathSaveServer + nameFile);
    file->open(QFile::WriteOnly);
    QDataStream saveStream(file);

    while (lBytesDone < lSize)
    {
        lBytes = 0;
        while (lBytes == 0)
            lBytes = pClientSocket->waitForReadyRead(-1);
        QByteArray block = pClientSocket->readAll();
        saveStream.writeRawData(block.data(), block.size());
        lBytesDone += block.size();
    }
    return nameFile;
}

void ServerSocket::sendFile(QTcpSocket* pClientSocket, QString nameFile)
{
    QFile* file = new QFile(pathSaveServer + nameFile);
    file->open(QFile::ReadOnly);

    QByteArray block;
    QDataStream sendStream(&block, QIODevice::WriteOnly);

    quint64 size = file->size();
    sendStream << quint16(MESSAGE_FILE)<< quint64(size) << QFileInfo(file->fileName()).fileName();

    pClientSocket->write(block);
    pClientSocket->flush();

    QDataStream read(file);
    quint64 lBytes = 0;

    char *buff = (char*)malloc(sizeof(char) * 1024);
    buff[1023] = '\0';

    while(!read.atEnd())
    {
        int readData = read.readRawData(buff, sizeof(char) * 1023);
        QByteArray blockData(buff, sizeof(char) * readData);

        lBytes += pClientSocket->write(blockData, sizeof(char) * readData);
        pClientSocket->flush();
//        if (lBytes == -1)
//        {
//            qWarning() << "Error";
//            pClientSocket->close();
//            return;
//        }
    }
    free((void*)buff);
}


QHash<QString, QTcpSocket*>::iterator ServerSocket::nameClient(QTcpSocket* client)   // запись таблицы клиента с сокетом client
{
    for (QHash<QString, QTcpSocket*>::iterator allClients = clients.begin(); allClients != clients.end(); allClients++)
        if (allClients.value() == client)   // нашли клиента
            return allClients;
}
