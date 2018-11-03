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

Employee * HireDirective::hiredEmployee() const
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
int HireDirective::insert() const
{
    return -1;
}
bool HireDirective::createDbTable()
{
     if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        if(query->exec("CREATE TABLE IF NOT EXISTS `hire_direcrive` (`id` INT(11) NOT NULL AUTO_INCREMENT, `hire_date` DATE, `fio` CHAR(30) ,`payform` INT(11),`salary` FLOAT(11),`employee_id` INT(11), PRIMARY KEY(`id`))"))
            return true;
        else
        {
            QString s = query->lastError().text();
            s+="as";
            return false;
        }
        delete query;
    }
    else
    {
        return false;
    }
}