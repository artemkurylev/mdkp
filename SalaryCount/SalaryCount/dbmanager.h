#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <qsql.h>
#include <qstring.h>
#include <qsqldatabase.h>
#include <qsqlquery.h>
#include "qsqlerror.h"

struct DbConf
{
	QString hostName, dbName, userName, pass;
	int port;
};

class DbManager : public QObject
{
    Q_OBJECT

public:
    DbManager();

    DbManager(const QString& hostName, const QString& dbName, int port,const QString& userName, const QString& pass);

    ~DbManager();

    QSqlQuery* makeQuery();
    bool checkConnection();
    static DbManager& manager();
    static DbManager& companyManager();
    static void closeConnection(){globalManager->db.close();}
private:
    QSqlDatabase db;
    QSqlDatabase companyDb;
    QSqlQuery _query;

    static DbManager* globalManager;
    static DbManager* _companyManager;
    static bool singletonCompanyExists;
    static bool singletonExists;
};

#endif // DBMANAGER_H
