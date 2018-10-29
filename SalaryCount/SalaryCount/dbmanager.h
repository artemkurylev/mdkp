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
    DbManager();

    DbManager(QString hostName, QString dbName, int port,QString userName, QString pass);

    ~DbManager();

    QSqlQuery* makeQuery();
    bool checkConnection();
    static DbManager& manager();
    static void closeConnection(){globalManager->db.close();}
private:
    QSqlDatabase db;
    QSqlQuery _query;

    static DbManager* globalManager;
    static bool singletonExists;
};

#endif // DBMANAGER_H
