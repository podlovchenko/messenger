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
#include <string>

class MyTcpClient : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpClient(QObject *parent = 0);

    QString file;
public slots:
    void slotRead();
    void sendString(const QString&, int);
    void setName(QString);
    QString getInterlocutor(void);
    void setInterlocutor(QString);
    bool verification(QString name);
    void sendFile(QString path);
    QString getFile(void);
private:
    QTcpSocket* mTcpSocket;
    QString name;
    QString interlocutor;

    size_t countOfNewMessange;
    void readHistoryChat(QDataStream&);
signals:
    void messageRecieve(QString message, bool flag);
    void newClientConnected(QString client);
    void clientDisconnected(QString client);
    void currentInterlocutor(QString interlocutor);
    void clearChat();
};
// кому отправляем
#endif // MYTCPCLIENT

