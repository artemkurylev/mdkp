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
    ~Employee();

private:
    QDate hireDate;
    QString fio[3];
    QString phoneNumber;
    int INN[10];
    int nextDutyChart;
    QDate nextDutyChartSince;
};

#endif // EMPLOYEE_H
