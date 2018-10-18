#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <qsql.h>

class DbManager : public QObject
{
    Q_OBJECT

public:
    DbManager(QObject *parent);

    ~DbManager();


private:
    
};

#endif // DBMANAGER_H
