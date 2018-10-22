#pragma once

#include "dbrecord.h"
#include "employee.h"
#include "BookKeeper.h"

	/*! Приказ о приёме нового сотрудника. Фиксирует зарплату и форму оплаты труда (помесячная/почасовая)
*/
class HireDirective :
	public DbRecord
{
public:
	HireDirective(QObject *parent);
	HireDirective(QDate hireDate, QString fio, PayForm payForm, float salary, int employeeID);
	~HireDirective(void);

	// getters
	QDate hireDate()	{	return _hireDate;	}
	QString fio()		{	return _fio;		}
	PayForm payForm()	{	return _payForm;	}
	float salary()		{	return _salary;		}

	Employee * hiredEmployee();

private:
	QDate _hireDate;
	QString _fio;
	PayForm _payForm;
	float _salary;

	// DB links
	int employeeID;
};
