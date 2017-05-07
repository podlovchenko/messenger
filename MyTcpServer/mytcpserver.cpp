#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include <QDataStream>

MyTcpServer::MyTcpServer(QObject *parent, int port) : QObject(parent), m_msgSize(-1)
{
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, port))
    {
        qDebug() << "server is not started";
    }
    else
    {
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection()
{
    mTcpSocket = mTcpServer->nextPendingConnection();
    //clients.push_back(mTcpSocket);

    QString str = "Hello I am your server!";
    sendString(str);

    connect(mTcpSocket, &QTcpSocket::readyRead,  this, &MyTcpServer::slotRead);
}

void MyTcpServer::sendString(const QString& str)
{
  QByteArray block;
  QDataStream sendStream(&block, QIODevice::ReadWrite);
  sendStream << quint16(0) << str;
  sendStream.device()->seek(0);
  sendStream << (quint16)(block.size() - sizeof(quint16));
  mTcpSocket->write(block);
}

void MyTcpServer::slotRead()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QString buff;
    QDataStream stream(pClientSocket);
    while(true)
    {
      if (m_msgSize < 0)
      {         
         if (pClientSocket->bytesAvailable() < sizeof(int))
           return;
         stream >> m_msgSize;
      }
      else
      {

        if (pClientSocket->bytesAvailable() < m_msgSize)
           return;   
        stream >> buff;
        sendString(buff);
        m_msgSize = -1;
      }
    }
}


