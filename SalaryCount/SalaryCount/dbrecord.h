#ifndef DBRECORD_H
#define DBRECORD_H

#include <QObject>
#include "dbmanager.h"
class DbRecord : public QObject
{
    Q_OBJECT

public:
    DbRecord(QObject *parent);
    ~DbRecord();
    
    virtual bool fetch() = 0;
    
    virtual bool set() = 0;
    
    virtual bool validate() = 0;
    
    virtual bool update() = 0;


protected:
    /*!< ������ ��� ������� � ���� ������ MYSQL */
    QString query;
    

};

#endif // DBRECORD_H
