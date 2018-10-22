#ifndef DBRECORD_H
#define DBRECORD_H

#include <QObject>
//#include "dbmanager.h"

class DbRecord : public QObject
{
    Q_OBJECT

public:
    DbRecord(QObject *parent);
	DbRecord(int id);
	DbRecord(const DbRecord & other);
    ~DbRecord();
    
    virtual bool fetch() = 0;
    
    virtual bool set() = 0;
    
    virtual bool validate() const = 0;
    
    virtual bool update() const = 0;

    int id() const;
protected:

    /*! Строка для запроса к базе данных MYSQL */
    QString query;

private:
    int _id;

};

#endif // DBRECORD_H
