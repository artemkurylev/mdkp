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

    int getId();
protected:
    /*!< ������ ��� ������� � ���� ������ MYSQL */
    QString query;
private:
    int id;

};

#endif // DBRECORD_H
