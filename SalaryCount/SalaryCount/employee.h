#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QObject>
#include <qdatetime.h>
#include <qstring.h>
#include "dutychart.h"
#include "dbrecord.h"

class Employee : public DbRecord
{
    Q_OBJECT

public:
    Employee(QObject *parent);
	Employee(int id);
    static bool createDbTable();
    bool fetch();
    ~Employee();

	bool fetch(){return false;}
    
	bool set(){return false;}
    
	bool validate() const {return false;}
    
	bool update() const {return false;}

private:
    QDate hireDate;
    QString fio;
    QString phoneNumber;
    int INN[10];
    int nextDutyChart;
    QDate nextDutyChartSince;
};

#endif // EMPLOYEE_H
