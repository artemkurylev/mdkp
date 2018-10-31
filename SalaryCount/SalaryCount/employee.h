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
    QString _fio;
    QString _phoneNumber;
    int _INN;
    int _nextDutyChart;
    QDate _hireDate;
    int _currentDutyChart;
    QDate _nextDutyChartSince;
};

#endif // EMPLOYEE_H
