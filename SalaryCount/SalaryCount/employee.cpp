#include "employee.h"

Employee::Employee(QObject *parent)
    : DbRecord(parent)
{
}
Employee::Employee(int id)
    : DbRecord(id)
{
}
bool Employee::createDbTable(){
    if(DbManager::manager().checkConnection()){
        QSqlQuery* query = DbManager::manager().makeQuery();
        if(query->exec("CREATE TABLE IF NOT EXISTS `employee` (`id` INT(11) NOT NULL AUTO_INCREMENT, `fio` CHAR(30) NOT NULL, `phone_number` CHAR(20),`hire_date` DATE,`dutychart_id` INT(11), PRIMARY KEY(`id`))"))
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
Employee::~Employee()
{

}

