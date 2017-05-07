#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
//#include "../MyTcpClient/mytcpclient.h"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0,int port = 6000);

public slots:
    void slotNewConnection();

    void slotRead();
    void sendString(const QString&);

private:
    QTcpServer * mTcpServer;
    QTcpSocket* mTcpSocket;
    //QVector<QTcpSocket*> clients;
    qint16 m_msgSize;
};

#endif // MYTCPSERVER_H
