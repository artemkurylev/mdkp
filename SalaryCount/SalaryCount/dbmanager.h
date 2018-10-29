#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <qsql.h>
#include <qstring.h>
#include <qsqldatabase.h>
#include <qsqlquery.h>
#include "qsqlerror.h"

class DbManager : public QObject
{
    Q_OBJECT

public:
    DbManager(QObject *parent);

    DbManager(QString hostName, QString dbName, int port,QString userName, QString pass);

    ~DbManager();

    bool makeQuery(QSqlQuery* query);
    bool checkConnection();
private:
    QSqlDatabase db;
};

#endif // DBMANAGER_H
