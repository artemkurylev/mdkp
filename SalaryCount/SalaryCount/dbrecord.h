#ifndef DBRECORD_H
#define DBRECORD_H

#include <QObject>

class DbRecord : public QObject
{
    Q_OBJECT

public:
    DbRecord(QObject *parent);

    ~DbRecord();

    virtual bool fetch() = 0;
    
    virtual bool set() = 0;
    
    virtual bool validate() const = 0;
    
    virtual bool update() const = 0;

    int id() const;

    /*! Строка для запроса к базе данных MYSQL */
    QString query;

private:
    int _id;

    virtual bool validate() = 0;
    
    virtual bool update() = 0;


private:
    
};

#endif // DBRECORD_H
