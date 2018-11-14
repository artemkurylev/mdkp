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
    Employee();
	Employee(int id);
    ~Employee();
    bool fetch();
    bool update() const;
    int insert();
    static bool createDbTable();
    static QMap<int,QString> getAll();
    static long countEntries();
    const HireDirective* hireDirective() const;

private:
	// ������
    QString _fio;
    QString _phoneNumber;
    int _INN;

	// ������
    int _nextDutyChart;
    int _currentDutyChart;
    QDate _nextDutyChartSince;

	// DB links
	int _hireDirectiveID;

	//const QString& tableName() { return "employee";};
};

#endif // EMPLOYEE_H
