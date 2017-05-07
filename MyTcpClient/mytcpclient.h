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

public slots:
    void slotRead();
    void sendString(const QString&);
    void bytesWritten(qint64 bytes);

private:
    QTcpSocket * mTcpSocket;
    qint16 m_msgSize;
    std::string name;
};

#endif // MYTCPCLIENT

