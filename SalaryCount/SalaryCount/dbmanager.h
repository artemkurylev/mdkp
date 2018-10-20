#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <qsql.h>
#include <qstring.h>
#include <qsqldatabase.h>

class DbManager : public QObject
{
    Q_OBJECT

public:
    DbManager(QObject *parent);

    DbManager(QObject *parent, QString hostName, QString dbName, int port, QString pass);

    ~DbManager();


private:
    QSqlDatabase db;
};

#endif // DBMANAGER_H
