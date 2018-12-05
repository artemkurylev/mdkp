#ifndef COMPANY_H
#define COMPANY_H

#include "dbrecord.h"

class Company : public DbRecord
{
    Q_OBJECT

public:
    Company(QObject *parent = 0);
    Company(QString name,QString pass){_name=name;_pass=pass;}
    ~Company();
    //Getter
    QString name(){return this->_name;}
    //Наследуемые методы
    int insert(){return -1;}
    bool update() const{return false;}
    bool fetch(){return false;}
    bool validate() const{return false;}
    //Статические методы
    static QMap<int,QString> getAll(){QMap<int,QString> records; return records;}
    static bool createTable();
    bool auth();
    
private:
    QString _name;
    QString _pass;
};

#endif // COMPANY_H
