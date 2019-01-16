#ifndef COMPANY_H
#define COMPANY_H

#include "dbrecord.h"
#include<qdatetime.h>
class Company : public DbRecord
{
    Q_OBJECT

public:
    Company(QObject *parent = 0);
    Company(QString name,QString pass, QDate date = QDate::currentDate()){_name=name;_pass=pass;_creationDate=date;}
    ~Company();

    //Getter
    QString name(){return this->_name;}
    QDate date(){return this->_creationDate;}
    //����������� �����
    int insert();
    bool update() const{return false;}
    bool fetch(){return false;}
    bool validate() const;
    //����������� ������
    static int countEntries();
    static QMap<int,QString> getAll();
    static bool createTable();
    bool auth();

	/*static*/
	static Company* currentCompany;
    
private:
    QString _name;
    QString _pass;
    QDate _creationDate;
};
void initializeCompany();
#endif // COMPANY_H
