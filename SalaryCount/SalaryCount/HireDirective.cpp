#include "HireDirective.h"


HireDirective::HireDirective(QObject *parent)
    : DbRecord(parent)
{
}
HireDirective::HireDirective(QDate hireDate, QString fio, PayForm payForm, float salary, int employeeID)
    : DbRecord(NULL)
{
	// TODO
}


HireDirective::~HireDirective(void)
{
}

Employee * HireDirective::hiredEmployee()
{
	return new Employee(employeeID);
}
