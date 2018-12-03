#ifndef COMPANY_H
#define COMPANY_H

#include "dbrecord.h"

class Company : public DbRecord
{
    Q_OBJECT

public:
    Company(QObject *parent = 0);
    ~Company();
    //Getter
    QString name(){return this->_name;}
    //Наследуемые методы
    int insert(){return -1;}
    bool update() const{return false;}
    bool fetch(){return false;}
    bool validate() const{return false;}
private:
    QString _name;    
};

#endif // COMPANY_H
