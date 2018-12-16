#include "HireDirective.h"
#include "employee.h"


HireDirective::HireDirective()
    : DbRecord()
{
	_hiredEmployee = NULL;
}
HireDirective::HireDirective(int id)
    : DbRecord(id)
{
	_hiredEmployee = NULL;
}
HireDirective::HireDirective(int id, QDate hireDate, QString fio, PayForm payForm, float salary, int employeeID)
    : DbRecord(NULL)
{
	this->_id = id;
	this->_hireDate = hireDate;
	this->_fio = fio;
	this->_payForm = payForm;
	this->_salary = salary;

	this->_employeeID = employeeID;

	_hiredEmployee = NULL;
}


HireDirective::~HireDirective(void)
{
	// free allocated record
	if(_hiredEmployee != NULL)
	{
		delete _hiredEmployee;
	}
}

Employee * HireDirective::hiredEmployee()
{
	if(_hiredEmployee == NULL)
	{
		_hiredEmployee = new Employee(_employeeID);
	}
	return _hiredEmployee;
}


bool HireDirective::fetch()
{
	bool success = false;
	if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

        query->prepare("SELECT * FROM `hire_directive` WHERE `id` = :id");
        int id = this->id();
        query->bindValue(":id",id);
        if(query->exec())
        {
            if(query->next())
            {
                _hireDate = query->value(1).toDate();
                _fio = query->value(2).toString();
                _payForm = (PayForm)query->value(3).toInt();
                _salary = query->value(4).toFloat();
                _employeeID = query->value(5).toInt();
				success = true;
            }
        }
        else
        {
            QString s = query->lastError().text();
            s+="as";
        }
        delete query;
    }
    return success;
}
    
bool HireDirective::validate() const
{
	return true;
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
int HireDirective::insert()
{
	int insert_id = -1;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("INSERT INTO `hire_directive` (hire_date,fio,payform,salary,employee_id) VALUES(:hire_date,:fio,:payform,:salary,:employee_id)");
        query->bindValue(":hire_date",this->_hireDate);
        query->bindValue(":fio",this->_fio);
        query->bindValue(":payform",this->_payForm);
        query->bindValue(":salary",this->_salary);
        query->bindValue(":employee_id",this->_employeeID);
        if(query->exec())
        {
			QVariant last_id = query->lastInsertId();
            if(last_id.isValid())
			{
                this->_id = last_id.toInt();
                insert_id = this->_id;
			}
        }
        else
        {
            QString s = query->lastError().text();
            s+="as";
        }
        delete query;
    }
    else
    {
    }
	return insert_id;
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
QMap<int,QString> HireDirective::getAll()
{
    QMap<int,QString> result;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("SELECT `id`,`fio` FROM `hire_directive`");
        if(query->exec())
        {
            while(query->next())
            {
                result[query->value(0).toInt()] = query->value(1).toString();
            }
        }
        delete query;
    }
    return result;
}
int HireDirective::countEntries()
{
    int counter = 0;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

        query->prepare("SELECT COUNT(*) FROM `hire_directive`");
        if(query->exec())
        {
            if(query->next())
                counter = query->value(0).toInt();
        }
        delete query;
    }
    return counter;
}
int HireDirective::lastDirectiveId()
{
    int id = -1;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

        query->prepare("SELECT MAX(`id`) FROM `hire_directive`;");
        if(query->exec())
        {
            if(query->next())
                id = query->value(0).toInt();
        }
        delete query;
    }
    return id;
}