#ifndef MYTCPCLIENT
#define MYTCPCLIENT

#include <QDebug>
#include <QCoreApplication>
#include <QIODevice>
#include <QDataStream>
#include <QTime>
#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QFile>
#include <QFileInfo>

const size_t MESSAGE_TEXT_TO = 0;
const size_t MESSAGE_TEXT_FROM = 10;
const size_t SEVERAL_MESSAGES = 25;
const size_t MESSAGE_FILE = 200;
const size_t RAW_FILE = 201;

const size_t NAME_CLIENT = 1;
const size_t NAME_INTERLOCUTOR = 2;
const size_t DEL_INTERLOCUTOR = 3;

const QString pathSave = "../Downloads/";

class MyTcpClient : public QObject
{
	Q_OBJECT

public:
    explicit MyTcpClient(QObject *parent = 0,size_t port = 6000);


    void readSeveralMessages(QDataStream&);
    void saveFile(QDataStream &stream);
    void clientOff(void);

public slots:
	void slotRead();
	void sendString(const QString&, int);

	bool verification(QString name);
    void sendFile(QString);


    QString getInterlocutor(void);
    QString getName(void);

    void setInterlocutor(QString);
    void setName(QString);

private:
	QTcpSocket* mTcpSocket;
	QString name;
	QString interlocutor;


signals:
	void messageRecieve(QString message, bool flag);
	void newClientConnected(QString client);
	void clientDisconnected(QString client);
	void currentInterlocutor(QString interlocutor);
	void clearChat();
    void end();
};

#endif // MYTCPCLIENT

