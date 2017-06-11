#ifndef SERVERSOCKET
#define SERVERSOCKET

#include "../Database/database.h"

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

class ServerSocket : public QObject
{
	Q_OBJECT

public:
	explicit ServerSocket(QObject *parent = 0);
    ~ServerSocket();

    void addClient(QTcpSocket*, QString);
    void whomToSend(QTcpSocket*, QString);
    void showAllClients(QTcpSocket*, QString);
    void sendHistory(QTcpSocket*, QTcpSocket*);
    QHash<QString, QTcpSocket*>::iterator nameClient(QTcpSocket*);
    QString saveFile(QDataStream& stream, QTcpSocket*);
    void sendFile(QTcpSocket*, QString);
    void sendString(QTcpSocket*, const QString&, int);
    void connectSignals(QTcpSocket*);
public slots:	
    void clientDisconnected();
	void slotRead();
	


private:
    DataBase db;

	QHash<QString, QTcpSocket*> clients;

	QHash<QString, QTcpSocket*> interlocutors;

	const size_t MESSAGE_TEXT_TO = 0;
	const size_t MESSAGE_TEXT_FROM = 10;
	const size_t MESSAGE_FILE = 200;
	const size_t RAW_FILE = 201;
	const size_t SEVERAL_MESSAGES = 25;

	const size_t NAME_CLIENT = 1;
	const size_t NAME_INTERLOCUTOR = 2;
	const size_t DEL_INTERLOCUTOR = 3;

    const size_t TYPE_TEXT = 1;
    const size_t TYPE_FILE = 2;

    const QString pathSaveServer = "../Uploads/";

};

#endif // SERVERSOCKET

