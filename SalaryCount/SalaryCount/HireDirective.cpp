#include "HireDirective.h"


HireDirective::HireDirective(QObject *parent)
    : DbRecord(parent)
{
}
HireDirective::HireDirective(QDate hireDate, QString fio, PayForm payForm, float salary, int employeeID)
    : DbRecord(NULL)
{
	this->_hireDate = hireDate;
	this->_fio = fio;
	this->_payForm = payForm;
	this->_salary = salary;

	this->_employeeID = employeeID;
}


HireDirective::~HireDirective(void)
{
}

Employee * HireDirective::hiredEmployee()
{
	return NULL; // new Employee(_employeeID);
}


bool HireDirective::fetch()
{
	return false;
}
    
bool HireDirective::set()
{
	return false;
}
    
bool HireDirective::validate() const
{
	return false;
}
    
bool HireDirective::update() const
{
	return false;
}
