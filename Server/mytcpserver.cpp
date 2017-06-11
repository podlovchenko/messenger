#include "mytcpserver.h"

MyTcpServer::MyTcpServer(QObject* parent, int port) : QObject(parent)
{
	mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);

    mTcpServer->listen(QHostAddress::Any, port);

    qDebug() << "Server is started. It is listening your...";	

    serverSocket = new ServerSocket(this);
}

MyTcpServer::~MyTcpServer()
{
    delete serverSocket;
}

void MyTcpServer::slotNewConnection() // клиент подключился
{
	QTcpSocket* mTcpSocket = mTcpServer->nextPendingConnection();   //  его слот

    serverSocket->connectSignals(mTcpSocket);
}

