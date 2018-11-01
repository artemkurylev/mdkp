#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QObject>
#include <qdatetime.h>
#include <qstring.h>
#include "dbrecord.h"
#include "dutychart.h"
#include "HireDirective.h"

class Employee : public DbRecord
{
    Q_OBJECT

public:
    Employee(QObject *parent);
	Employee(int id);
    ~Employee();
    bool fetch();
    int insert() const;
    static bool createDbTable();

    const HireDirective* hireDirective() const;

	bool fetch(){return false;}
    
	bool set(){return false;}
    
	bool validate() const {return false;}
    
	bool update() const {return false;}

private:
	// личные
    QString _fio;
    QString _phoneNumber;
    int _INN;

	// график
    int _nextDutyChart;
    int _currentDutyChart;
    QDate _nextDutyChartSince;

	// DB links
	int _hireDirectiveID;
};

#endif // EMPLOYEE_H
