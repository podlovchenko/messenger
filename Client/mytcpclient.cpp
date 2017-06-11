#include "mytcpclient.h"


MyTcpClient::MyTcpClient(QObject *parent,size_t port) : QObject(parent)
{
	mTcpSocket = new QTcpSocket(this);
    mTcpSocket->connectToHost("127.0.0.1", port, QIODevice::ReadWrite);
	connect(mTcpSocket, SIGNAL(readyRead()), this, SLOT(slotRead()));
    connect(mTcpSocket, &QTcpSocket::disconnected, this, &MyTcpClient::clientOff); // клиент отключился
}

void MyTcpClient::clientOff(void)
{
    delete mTcpSocket;
    emit end();
}

void MyTcpClient::slotRead() // читаем сообщение от сервера
{
	QDataStream stream(mTcpSocket);

	qint16 type;
	stream >> type;     // определяем тип сообщения

    if (type == MESSAGE_FILE)
    {
        saveFile(stream);
		return;
	}

	QString buff;
	qint16 m_msgSize = -1;

	while (true)
	{
		if (m_msgSize < 0)
		{
			if (mTcpSocket->bytesAvailable() < sizeof(int))
				return;
			stream >> m_msgSize;
		}

		else
		{
			if (mTcpSocket->bytesAvailable() < m_msgSize || mTcpSocket->bytesAvailable() == 0)
				return;

			stream >> buff;

            if (type == MESSAGE_TEXT_TO) // прием сообщения от себя же
			{
				emit messageRecieve(QString(buff), true);
			}

            if (type == MESSAGE_TEXT_FROM) // прием сообщения от собеседника
			{
				emit messageRecieve(QString(buff), false);
			}

            else if (type == NAME_CLIENT) // прием нового клиента
			{
				emit newClientConnected(QString(buff));
			}

            else if (type == NAME_INTERLOCUTOR) // прием отправителя сообщения
			{
				;
			}

            else if (type == DEL_INTERLOCUTOR) // удалить собеседника из списка
            {
				emit clientDisconnected(QString(buff));
            }

            else if (type == SEVERAL_MESSAGES) // считать несколько сообщений
			{
                readSeveralMessages(stream);
				return;
			}



			m_msgSize = -1;
		}
	}
}

void MyTcpClient::readSeveralMessages(QDataStream& stream)
{
	QString buff;
    qint16 type = -1;
	qint16 m_msgSize = -1;

	while (true)
	{
		if (m_msgSize < 0)
		{
			if (mTcpSocket->bytesAvailable() < sizeof(int))
				return;

            if (type < 0)
				stream >> type;

			stream >> m_msgSize;
		}

		else
		{

			if (mTcpSocket->bytesAvailable() < m_msgSize || mTcpSocket->bytesAvailable() == 0)
				return;

			stream >> buff;

            if (type == MESSAGE_TEXT_TO) // прием сообщения от себя же
			{
				emit messageRecieve(QString(buff), true);
			}

            else if (type == MESSAGE_TEXT_FROM) // прием сообщения от собеседника
			{
				emit messageRecieve(QString(buff), false);
			}

            else if (type == NAME_CLIENT) // прием нового клиента
            {
                emit newClientConnected(QString(buff));
            }

			m_msgSize = -1;
            type = -1;
		}
	}
}

void MyTcpClient::sendString(const QString& str, int type)  // отправляем сообщение серверу
{
	QByteArray block;
	QDataStream sendStream(&block, QIODevice::ReadWrite);
    sendStream << quint16(0) << quint16(0) << str;
	sendStream.device()->seek(0);
	sendStream << (quint16)(type) << (quint16)(block.size() - 2 * sizeof(quint16));
	mTcpSocket->write(block);
}


void MyTcpClient::sendFile(QString path)
{
    path.remove("file://");
    QFile* file = new QFile(path);
    file->open(QFile::ReadOnly);

    QByteArray block;
    QDataStream sendStream(&block, QIODevice::WriteOnly);

    quint64 size = file->size();
    sendStream << quint16(MESSAGE_FILE)<< quint64(size) << QFileInfo(file->fileName()).fileName();

    mTcpSocket->write(block);
    mTcpSocket->flush();

    QDataStream read(file);

    quint64 lBytes = 0;

    char *buff = (char*)malloc(sizeof(char) * 1024);
    buff[1023] = '\0';
    while(!read.atEnd())
    {
        int readData = read.readRawData(buff, sizeof(char) * 1023);
        QByteArray blockData(buff, sizeof(char) * readData);

        lBytes += mTcpSocket->write(blockData, sizeof(char) * readData);
        mTcpSocket->flush();
        if (lBytes == -1)
        {
            qWarning() << "Error";
            mTcpSocket->close();
            return;
        }
    }
    free((void*)buff);
}

void MyTcpClient::saveFile(QDataStream &stream)
{
    quint64 lBytesDone = 0;
    quint64 lSize = 0;
    quint64 lBytes = 0;
    QString nameFile;

    stream >> lSize >> nameFile;
    QFile* file = new QFile(pathSave + nameFile);
    file->open(QFile::WriteOnly);
    QDataStream saveStream(file);

    while (lBytesDone < lSize)
    {
        lBytes = 0;
        //while (lBytes == 0)
        //    lBytes = mTcpSocket->waitForReadyRead(-1);
        QByteArray block = mTcpSocket->readAll();
        saveStream.writeRawData(block.data(), block.size());
        lBytesDone += block.size();
    }
}


void MyTcpClient::setName(QString client_name)
{
	name = client_name;
}

void MyTcpClient::setInterlocutor(QString client_name)
{
    emit currentInterlocutor(interlocutor);         // смена фокуса на собеседника
    emit clearChat();                               // удаление старого чата изменившего собеседника
	interlocutor = client_name;
}

QString MyTcpClient::getInterlocutor(void)
{
	return interlocutor;
}

QString MyTcpClient::getName(void)
{
    return name;
}

bool MyTcpClient::verification(QString name)
{
	if (name.length() == 0)
		return false;
	// пробить на сервере этот ник
    // если надо добавить в бд
	return true;
}
