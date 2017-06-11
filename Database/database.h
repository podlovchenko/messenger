#ifndef DATABASE_H
#define DATABASE_H

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
#include <QPair>

class DataBase : public QObject
{
    Q_OBJECT

public:
    explicit DataBase(QString pathDataBase);
    ~DataBase();
    void insert(int type, QString nameClient1, QString nameClient2, QString message);
    QVector<QPair<QString, bool> > getHistory(QString nameClient1, QString nameClient2);
private:
    QSqlDatabase db;
};

#endif // DATABASE_H

