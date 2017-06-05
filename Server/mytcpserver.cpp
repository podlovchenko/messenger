#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include <QDataStream>
#include <QDateTime>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>

QSqlDatabase db;

MyTcpServer::MyTcpServer(QObject *parent, int port) : QObject(parent)
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
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/seva/tmp/Messenger/history.db3");
    db.open();
}

MyTcpServer::~MyTcpServer()
{
    db.close();
    // цикл на дисконект с emit qt.exit и close сокета кадого clients
}

void MyTcpServer::slotNewConnection() // клиент подключился
{
    QTcpSocket* mTcpSocket = mTcpServer->nextPendingConnection();   //  его слот

    connect(mTcpSocket, &QTcpSocket::readyRead,  this, &MyTcpServer::slotRead); // возможность отловить сообщения от клиента
    connect(mTcpSocket, &QTcpSocket::disconnected, this, &MyTcpServer::clientDisconnected); // клиент отключился
}

void MyTcpServer::sendString(QTcpSocket* clientReceiver,const QString& str, int type)    // отправить сообщение клиенту
{
    if ( clientReceiver == 0 )
        return;

    QByteArray block;
    QDataStream sendStream(&block, QIODevice::ReadWrite);
    if ( type != -1)
    {
        sendStream << quint16(0) << quint16(0) << str; // отправляем тип и размер сообщения, сын
        sendStream.device()->seek(0);
        sendStream << (quint16) (type) << (quint16)(block.size() - 2 * sizeof(quint16));
    }
    else    // при type == -1 передача сообщения производиться без типа
    {
        sendStream << quint16(0) << str; // отправляем тип и размер сообщения
        sendStream.device()->seek(0);
        sendStream  << (quint16)(block.size() - sizeof(quint16));
    }

    clientReceiver->write(block);
}

QHash<QString, QTcpSocket*>::iterator MyTcpServer::nameClient(QTcpSocket* client)
{
    for(QHash<QString, QTcpSocket*>::iterator allClients = clients.begin(); allClients != clients.end(); allClients++)
        if ( allClients.value() == client)   // нашли клиента
            return allClients;
}

void MyTcpServer::clientDisconnected()
{
    QHash<QString, QTcpSocket*>::iterator client = nameClient( (QTcpSocket*)sender() );
    QString key = client.key();
    clients.erase(client);  // удаляем запись из хэш-таблицы

    for(QHash<QString, QTcpSocket*>::iterator allClients = clients.begin(); allClients != clients.end(); allClients++)
    {
        sendString(allClients.value(),key,3);  // удаляем у всех клиентов иконку удаленного
    }
}

void MyTcpServer::slotRead() // считать сообщение от клиента
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();

    QSqlQuery query;
    query.prepare("INSERT INTO message (id, user_to, user_from, message_text) VALUES (NULL, ?, ?, ?)");

    QDataStream stream(pClientSocket);

    qint16 type;
    stream >> type;     // определяем тип сообщения

    QString buff;
    qint16 m_msgSize = -1;

    while(true)
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

        if( type == 0 ) // отправка сообщения
        {
            QHash<QString, QTcpSocket*>::iterator client = nameClient(pClientSocket);
            QString name = client.key();    // имя отправителя
            query.addBindValue(name);

            QHash<QString, QTcpSocket*>::iterator client1 = nameClient(interlocutors.value(name));
            query.addBindValue(client1.key());

            if ( pClientSocket == interlocutors.value(name))
                sendString(interlocutors.value(name),buff,0); // сообщение в чате от себя
            else
                sendString(interlocutors.value(name),buff,10); // сообщение в чате от собеседника

            sendString(pClientSocket,buff,0); // напечатать это же сообщение у себя в чате
            query.addBindValue(buff);
            query.exec();
        }

        else if ( type == 1 ) // отправка своего имени
            addClient(pClientSocket,buff);

        else if ( type == 2 ) // отправка имени собеседника
            whomToSend(pClientSocket,buff);


        m_msgSize = -1;
      }
    }
}

void MyTcpServer::addClient(QTcpSocket* pClientSocket, QString buff)
{
    showAllClients(pClientSocket,buff); // добавить иконки клиентам

    clients.insert(buff,pClientSocket); // добавить запись о клиенте


    //for(QHash<QString, QTcpSocket*>::iterator allClients = clients.begin(); allClients != clients.end(); allClients++)
        //qDebug() << allClients.key();

}

void MyTcpServer::whomToSend(QTcpSocket* pClientSocket,QString name) // смена собеседника
{
    QHash<QString, QTcpSocket*>::iterator client = nameClient(pClientSocket);
    QString whoWrite = client.key();    // имя отправителя

    QTcpSocket* whoRead = clients.value(name);  // сокет получателя

    // запоминаем какому сокету пишет клиент
    if ( interlocutors.contains(whoWrite) == true)
        interlocutors[whoWrite] = whoRead;
    else
        interlocutors.insert(whoWrite,whoRead);


    // метод отсылающий клиенту историю сообщений с новым собеседником
    sendHistory(pClientSocket,clients.value(name)); // сокет клиента отправителя, сокет получателя
}

void MyTcpServer::sendHistory(QTcpSocket* clientSender,QTcpSocket* clientReceiver)
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
        QString to     = query.value(1).toString();
        QString m_text = query.value(3).toString();
        chat.append(m_text);
        time.push_back(QDateTime::currentDateTime());
        if (to == name1)
            initiator.push_back(true);
        else
            initiator.push_back(false);
    }
    
    sendString(clientSender,"",25);
    for(size_t i = 0; i < chat.size(); i++)
    {
       sendString(clientSender,chat[i],initiator[i] * 10);
    }

}

void MyTcpServer::showAllClients(QTcpSocket* pClientSocket, QString buff)
{

    bool flag = true;   // для одноразового захода
    // пробегаемся по каждому клиенту
    for(QHash<QString, QTcpSocket*>::iterator allClients = clients.begin(); allClients != clients.end(); allClients++)
    {
        // новому клиенту необходимо отобразить весь список собеседников

        if ( flag == false )
            sendString(pClientSocket,allClients.key(),-1);
        else
        {
            sendString(pClientSocket,allClients.key(),1);
            flag = false;
        }

        // каждому старому клиенту добавляем нового собеседника
        sendString(allClients.value(),buff,1);
    }

}
