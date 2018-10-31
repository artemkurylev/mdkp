#include "employee.h"

Employee::Employee()
    : DbRecord(0)
{
}
Employee::Employee(int id)
    : DbRecord(id)
{
}
bool Employee::createDbTable()
{
    if(DbManager::manager().checkConnection()){
        QSqlQuery* query = DbManager::manager().makeQuery();
        if(query->exec("CREATE TABLE IF NOT EXISTS `employee` (`id` INT(11) NOT NULL AUTO_INCREMENT, `fio` CHAR(30) NOT NULL, `phone_number` CHAR(20),`inn` INT(10),`hire_date` DATE,`dutychart_id` INT(11),`next_dutychart_id` INT(11),`next_dutychart_since` DATE, PRIMARY KEY(`id`))"))
            return true;
        else{
            QString s = query->lastError().text();
            s+="as";
            return false;
        }
        delete query;
    }
    else{
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
                _hireDate = query->value(4).toDate();
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
Employee::~Employee()
{

}

