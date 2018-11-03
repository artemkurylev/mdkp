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
	    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("UPDATE `hire_directive` SET hire_date = :hire_date , fio = :fio, payform = :payform, salary= :salary, employee_id= :employee_id WHERE id = :id");
        query->bindValue(":hire_date",this->_hireDate);
        query->bindValue(":fio",this->_fio);
        query->bindValue(":payform",this->_payForm);
        query->bindValue(":salary",this->_salary);
        query->bindValue(":employee_id",this->_employeeID);
        query->bindValue(":id", this->_id);
        if(query->exec())
        {
            delete query;
            return true;
        }
        else
        {
            delete query;
            return false;
        }
    }
    return false;
}
int HireDirective::insert() const
{
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("INSERT INTO `hire_directive` (hire_date,fio,payform,salary,employee_id) VALUES(:hire_date,:fio,:payform,:salary,:employee_id");
        query->bindValue(":hire_date",this->_hireDate);
        query->bindValue(":fio",this->_fio);
        query->bindValue(":payform",this->_payForm);
        query->bindValue(":salary",this->_salary);
        query->bindValue(":employee_id",this->_employeeID);
        if(query->exec())
        {
            if(query->exec("SELECT LAST_INSERT_ID()") && query->next())
                return query->value(0).toInt();
        }
        else
        {
            QString s = query->lastError().text();
            s+="as";
            return -1;
        }
        delete query;
    }
    else
    {
        return -1;
    }
}
bool HireDirective::createDbTable()
{
     if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        if(query->exec("CREATE TABLE IF NOT EXISTS `hire_directive` (`id` INT(11) NOT NULL AUTO_INCREMENT, `hire_date` DATE, `fio` CHAR(30) ,`payform` INT(11),`salary` FLOAT(11),`employee_id` INT(11), PRIMARY KEY(`id`))"))
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