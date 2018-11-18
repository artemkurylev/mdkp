#pragma once

#include "dbrecord.h"
//#include "employee.h"
#include "BookKeeper.h"

class Employee;

/*! Приказ о приёме нового сотрудника. Фиксирует зарплату и форму оплаты труда (помесячная/почасовая)
*/
class HireDirective :
	public DbRecord
{
public:
	HireDirective();
	HireDirective(int id);
	HireDirective(QDate hireDate, QString fio, PayForm payForm, float salary, int employeeID);
	~HireDirective(void);

	// getters
	QDate hireDate()	const	{	return _hireDate;	}
	QString fio()		const	{	return _fio;		}
	PayForm payForm()	const	{	return _payForm;	}
	float salary()		const	{	return _salary;		}

	// methods
	Employee * hiredEmployee();
    int lastDirectiveId();

	// inherited
	bool HireDirective::fetch();
	bool HireDirective::validate() const;
	bool HireDirective::update() const;
    int  HireDirective::insert();
    
    //static
    bool static createDbTable();
    static QMap<int,QString> getAll();
    static int countEntries();
private:
	QDate _hireDate;
	QString _fio;
	PayForm _payForm;
	float _salary;

	// DB links
	int _employeeID;

	// singleton-кэш записи
	Employee* _hiredEmployee; //! <default> = NULL;  приказ
};
