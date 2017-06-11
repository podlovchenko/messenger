#ifndef MYTCPSERVER
#define MYTCPSERVER

#include "../ServerSocket/serversocket.h"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QCoreApplication>
#include <QDataStream>
#include <QDateTime>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>

class MyTcpServer : public QObject
{
	Q_OBJECT

public:
	explicit MyTcpServer(QObject *parent = 0, int port = 6000);
	~MyTcpServer();

public slots:
	void slotNewConnection();

private:
	QTcpServer* mTcpServer;
    ServerSocket* serverSocket;

};

#endif // MYTCPSERVER

