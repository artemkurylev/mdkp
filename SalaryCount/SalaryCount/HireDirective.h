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
	HireDirective();
	HireDirective(QDate hireDate, QString fio, PayForm payForm, float salary, int employeeID);
	~HireDirective(void);

	// getters
	QDate hireDate()	const	{	return _hireDate;	}
	QString fio()		const	{	return _fio;		}
	PayForm payForm()	const	{	return _payForm;	}
	float salary()		const	{	return _salary;		}

	// methods
	Employee * hiredEmployee();

	// inherited
	bool HireDirective::fetch();
	bool HireDirective::set();
	bool HireDirective::validate() const;
	bool HireDirective::update() const;
    int HireDirective::insert() const;

private:
	QDate _hireDate;
	QString _fio;
	PayForm _payForm;
	float _salary;

	// DB links
	int _employeeID;
};
