#include "database.h"

DataBase::DataBase(QString pathDataBase) : QObject(0)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(pathDataBase);
    db.open();
}

DataBase::~DataBase()
{
    db.close();
}

void DataBase::insert(int type, QString nameClient1, QString nameClient2, QString message)
{
    QSqlQuery query;
    query.prepare("INSERT INTO message (id, type, user_from, user_to, message_text) VALUES (NULL, ?, ?, ?, ?)");

    query.addBindValue(type);
    query.addBindValue(nameClient1);
    query.addBindValue(nameClient2);
    query.addBindValue(message);

    query.exec();
}

QVector<QPair<QString, bool> > DataBase::getHistory(QString nameClient1, QString nameClient2)
{
    QVector<QPair<QString, bool> > history;
    QSqlQuery query;
    query.prepare("SELECT id, user_from, user_to, message_text FROM message WHERE user_from = ? AND user_to = ? OR user_to = ? AND user_from = ?");

    query.addBindValue(nameClient1);
    query.addBindValue(nameClient2);
    query.addBindValue(nameClient1);
    query.addBindValue(nameClient2);

    query.exec();

    while (query.next())
    {
        QString to = query.value(2).toString();
        QString text = query.value(3).toString();
        if (to == nameClient1)
            history.push_back(qMakePair(text, true));
        else
            history.push_back(qMakePair(text, false));
    }

    return history;
}
