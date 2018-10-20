#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QObject>
#include <qdatetime.h>
#include <qstring.h>
#include "dutychart.h"
class Employee : public QObject
{
    Q_OBJECT

public:
    Employee(QObject *parent);
    ~Employee();

private:
    QDate hireDate;
    QString fio[3];
    int nextDutyChart;
    QDate nextDutyChartSince;
};

#endif // EMPLOYEE_H
