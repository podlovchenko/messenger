#include "mytcpclient.h"
#include <iostream>

MyTcpClient::MyTcpClient(QObject *parent) : QObject(parent)
{
    mTcpSocket = new QTcpSocket(this);
    mTcpSocket->connectToHost("127.0.0.1", 6000,QIODevice::ReadWrite);
    qDebug() << "client is started";
    connect(mTcpSocket, SIGNAL(readyRead()),this,  SLOT(slotRead()));
    countOfNewMessange = 0;

    file = "lala"; // ЗДЕСЬ задается путь к передаваемому файлу
}

void MyTcpClient::sendFile(QString path)
{
    qDebug() << path;
}

QString MyTcpClient::getFile(void)
{
    return file;
}

void MyTcpClient::slotRead() // читаем сообщение от сервера
{
    QDataStream stream(mTcpSocket);

    qint16 type;
    stream >> type;     // определяем тип сообщения

    QString buff;
    qint16 m_msgSize = -1;


    while(true)
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

        if( type == 0 ) // прием сообщения от себя же
        {

            emit messageRecieve(QString(buff),true);
        }

        if ( type == 10 ) // прием сообщения от собеседника
        {
             //countOfNewMessange++;
             emit messageRecieve(QString(buff),false);
        }

        else if ( type == 1 ) // прием нового клиента
        {
            emit newClientConnected(QString(buff));
        }

        else if ( type == 2 ) // прием отправителя сообщения
            {;}
        else if ( type == 3 ) // удалить собеседника из списка
            emit clientDisconnected(QString(buff));
        else if ( type == 25 ) // считать историю чата
        {
            readHistoryChat(stream);
            return;
        }



        m_msgSize = -1;
      }
    }

}

void MyTcpClient::readHistoryChat(QDataStream& stream)
{
    QString buff;
    qint16 type = -10;
    qint16 m_msgSize = -1;


    while(true)
    {
      if (m_msgSize < 0)
      {
         if (mTcpSocket->bytesAvailable() < sizeof(int))
           return;

         if ( type == -10)
             stream >> type;

         stream >> m_msgSize;
      }
      else
      {

        if (mTcpSocket->bytesAvailable() < m_msgSize || mTcpSocket->bytesAvailable() == 0)
           return;

        stream >> buff;

        if( type == 0 ) // прием сообщения от себя же
        {
            emit messageRecieve(QString(buff),true);
        }

        if ( type == 10 ) // прием сообщения от собеседника
        {
             emit messageRecieve(QString(buff),false);
        }

        m_msgSize = -1;
        type = -10;
      }
    }
}

// клиент всегда отправляет по одному сообщению, type == -1 не нужен.
void MyTcpClient::sendString(const QString& str, int type)    // отправляем сообщение серверу
{
  QByteArray block;
  QDataStream sendStream(&block, QIODevice::ReadWrite);
  sendStream << quint16(0) << quint16(0) << str; // отправляем тип и размер сообщения, сын
  sendStream.device()->seek(0);
  sendStream << (quint16) (type) << (quint16)(block.size() - 2 * sizeof(quint16));
  mTcpSocket->write(block);
}

void MyTcpClient::setName(QString client_name)
{
    name = client_name;
}

void MyTcpClient::setInterlocutor(QString client_name)
{
    emit currentInterlocutor(interlocutor); // смена фокуса на собеседника

    emit clearChat();   // удаление старого чата изменившего собеседника

    interlocutor = client_name;   
}

QString MyTcpClient::getInterlocutor(void)
{
    return interlocutor;
}

bool MyTcpClient::verification(QString name)
{
    if (name.length() == 0)
        return false;
    // пробить на сервере этот ник
    return true;
}
