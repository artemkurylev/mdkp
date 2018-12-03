#include "company.h"

Company::Company(QObject *parent)
    : DbRecord(0)
{

}
bool Company::createTable()
{
    bool success = false;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        if(query->exec("CREATE TABLE IF NOT EXISTS `company` (`id` INT(11) NOT NULL AUTO_INCREMENT, `name` VARCHAR(30) UNIQUE"))
		{
            success = true;
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
    return success;
}
Company::~Company()
{

}
