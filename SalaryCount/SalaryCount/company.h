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
    //Наследуемые метод
    int insert();
    bool update() const{return false;}
    bool fetch(){return false;}
    bool validate() const{return false;}
    //Статические методы
    static int countEntries();
    static QMap<int,QString> getAll();
    static bool createTable();
    bool auth();

    
private:
    QString _name;
    QString _pass;
};
void initializeCompany();
#endif // COMPANY_H
