#include "employee.h"

Employee::Employee()
    : DbRecord(0)
{
}
Employee::Employee(int id)
    : DbRecord(id)
{
}
bool Employee::update() const
{
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("UPDATE `employee` SET fio = :fio , phone_number = :phone_number, inn = :inn, hire_directive_id = :hire_directive_id, dutychart_id = :dutychart_id, next_dutychart_id = :next_dutychart_id, next_dutychart_since = :next_dutychart_since WHERE `id` = id");
        query->bindValue(":fio",this->_fio);
        query->bindValue(":phone_number",this->_phoneNumber);
        query->bindValue(":inn",this->_INN);
        query->bindValue(":hire_directive_id",this->_hireDirectiveID);
        query->bindValue(":dutychart_id",this->_currentDutyChart);
        query->bindValue(":next_dutychart_id",this->_nextDutyChart);
        query->bindValue(":next_dutychart_since", this->_nextDutyChartSince);
        query->bindValue(":id", this->id());
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
bool Employee::createDbTable()
{
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        if(query->exec("CREATE TABLE IF NOT EXISTS `employee` (`id` INT(11) NOT NULL AUTO_INCREMENT, `fio` CHAR(30) NOT NULL, `phone_number` CHAR(20),`inn` INT(10),`hire_directive_id` INT(11),`dutychart_id` INT(11),`next_dutychart_id` INT(11),`next_dutychart_since` DATE, PRIMARY KEY(`id`))"))
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
bool Employee::fetch()
{
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

        query->prepare("SELECT * FROM `employee` WHERE `id` = :id");
        int id = this->id();
        query->bindValue(":id",id);
        if(query->exec())
        {
            if(query->next())
            {
                _fio = query->value(1).toString();
                _phoneNumber = query->value(2).toString();
                _INN = query->value(3).toInt();
				// hire_directive_id
				_hireDirectiveID = query->value(4).toInt();
                _currentDutyChart = query->value(5).toInt();
                _nextDutyChart = query->value(6).toInt();
                _nextDutyChartSince = query->value(7).toDate();
            }
        }
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
int Employee::insert() const
{
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("INSERT INTO `employee` (fio,phone_number,inn,hire_directive_id,dutychart_id) VALUES(:fio,:phone_number,:inn,:hire_directive_id,:dutychart_id");
        query->bindValue(":fio",this->_fio);
        query->bindValue(":phone_number",this->_phoneNumber);
        query->bindValue(":inn",this->_INN);
        query->bindValue(":hire_directive_id",this->_hireDirectiveID);
        query->bindValue(":dutychart_id",this->_currentDutyChart);
        if(query->exec())
        {
            query->prepare("SELECT id FROM `employee` WHERE `inn` = :inn");
            query->bindValue(":inn",this->_INN);
            if(query->exec() && query->next())
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
    else{
        return -1;
    }
}

Employee::~Employee()
{

}

const HireDirective * Employee::hireDirective() const
{

	return NULL; // new HireDirective(_hireDirectiveID);
}

