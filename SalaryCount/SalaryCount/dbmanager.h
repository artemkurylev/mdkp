#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <qsql.h>
#include <qstring.h>
#include <qsqldatabase.h>
#include <qsqlquery.h>

class DbManager : public QObject
{
    Q_OBJECT

public:
    DbManager(QObject *parent);

    DbManager(QString hostName, QString dbName, int port, QString pass);

    ~DbManager();

    bool makeQuery(QSqlQuery* query);

private:
    QSqlDatabase db;
};

#endif // DBMANAGER_H
