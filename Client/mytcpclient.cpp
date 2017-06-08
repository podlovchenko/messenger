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
    qDebug() << path;
    if (file->open(QFile::ReadOnly))
    {
        QByteArray block;
        QDataStream sendStream(&block, QIODevice::WriteOnly);
        quint16 size = file->size();
        sendStream << quint16(MESSAGE_FILE) << QFileInfo(file->fileName()).fileName() << quint16(size);
        // type, name, size
        char buff[1024];
        quint16 toFile;
        while (!file->atEnd())
        {
            toFile = file->read(buff, sizeof(buff)); // real size message
            sendStream << toFile;
            sendStream.writeRawData(buff, toFile);
        }
        file->close();
        mTcpSocket->write(block);
    }
    delete file;
}

void MyTcpClient::saveFile(QDataStream &stream)
{
    QDateTime time = QDateTime::currentDateTime();

    QString nameFile;
    stream >> nameFile;

    qint16 sizeReceiveFile;
    qint16 sizeReceivedData = 0;
    stream >> sizeReceiveFile;


    QString savePath = "../Downloads/" + nameFile;
    savePath += "[" + time.toString() + "]";
    QFile *File = new QFile(savePath);
    File->open(QFile::WriteOnly);

    char block[1024];
    qint16 toFile;

    while (true)
    {
        stream >> toFile;
        stream.readRawData(block, toFile);
        sizeReceivedData += toFile;
        File->write(block, toFile);
        if (sizeReceivedData == sizeReceiveFile)
        {
            File->close();
            return;
        }
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
