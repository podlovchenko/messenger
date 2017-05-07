#include "mytcpclient.h"
#include <iostream>

MyTcpClient::MyTcpClient(QObject *parent) : QObject(parent), m_msgSize(-1)
{
    //std::cout<<"Your name\n";
    //std::cin >> name;
    mTcpSocket = new QTcpSocket(this);
    mTcpSocket->connectToHost("127.0.0.1", 6000,QIODevice::ReadWrite);
    //sendString(name.c_str());
    qDebug() << "client is started";
    connect(mTcpSocket, SIGNAL(readyRead()),this,  SLOT(slotRead()));
    connect(mTcpSocket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));

}

void MyTcpClient::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void MyTcpClient::slotRead()
{
    QString buff;
    QDataStream stream(mTcpSocket);
    while(true)
    {
      if (m_msgSize < 0)
      {
         if (mTcpSocket->bytesAvailable() < sizeof(int))
           break;
         stream >> m_msgSize;
      }
      else
      {

        if (mTcpSocket->bytesAvailable() < m_msgSize)
           break;
        stream >> buff;
        qDebug() << buff;
        m_msgSize = -1;
      }
    }
}

void MyTcpClient::sendString(const QString& str)
{
  QByteArray block;
  QDataStream sendStream(&block, QIODevice::ReadWrite);
  sendStream << quint16(0) << str;
  sendStream.device()->seek(0);
  sendStream << (quint16)(block.size() - sizeof(quint16));
  mTcpSocket->write(block);
}
