#ifndef MYTCPSERVER
#define MYTCPSERVER

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QFile>
#include <QDebug>
#include <QCoreApplication>
#include <QDataStream>
#include <QDateTime>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>

const size_t MESSAGE_TEXT_TO = 0;
const size_t MESSAGE_TEXT_FROM = 10;
const size_t MESSAGE_FILE = 200;
const size_t RAW_FILE = 201;
const size_t SEVERAL_MESSAGES = 25;

const size_t NAME_CLIENT = 1;
const size_t NAME_INTERLOCUTOR = 2;
const size_t DEL_INTERLOCUTOR = 3;



class MyTcpServer : public QObject
{
	Q_OBJECT

public:
	explicit MyTcpServer(QObject *parent = 0, int port = 6000);
	~MyTcpServer();

    void addClient(QTcpSocket*, QString);
    void whomToSend(QTcpSocket*, QString);
    void showAllClients(QTcpSocket*, QString);
    void sendHistory(QTcpSocket*, QTcpSocket*);
    QHash<QString, QTcpSocket*>::iterator nameClient(QTcpSocket*);
    void sendFile(QDataStream& stream, QTcpSocket*);
    void saveFile(QDataStream& stream,int);
public slots:
	void slotNewConnection();
    void clientDisconnected();
	void slotRead();
	void sendString(QTcpSocket*, const QString&, int);


private:
	QTcpServer* mTcpServer;
    QSqlDatabase db;

	QHash<QString, QTcpSocket*> clients;

	QHash<QString, QTcpSocket*> interlocutors;

};

#endif // MYTCPSERVER

