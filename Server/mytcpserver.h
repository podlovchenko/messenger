#ifndef MYTCPSERVER
#define MYTCPSERVER

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0,int port = 6000);
    ~MyTcpServer();
public slots:
    void slotNewConnection();

    void slotRead();
    void sendString(QTcpSocket*,const QString&,int);

private:
    QTcpServer* mTcpServer;
    //QTcpSocket* mTcpSocket;

    QHash<QString, QTcpSocket*> clients;

    QHash<QString, QTcpSocket*> interlocutors;

    void addClient(QTcpSocket*, QString);
    void whomToSend(QTcpSocket*,QString);
    void showAllClients(QTcpSocket*, QString);
    void clientDisconnected();
    void sendHistory(QTcpSocket*,QTcpSocket*);
    QHash<QString, QTcpSocket*>::iterator nameClient(QTcpSocket*);
};

#endif // MYTCPSERVER

