#include "BillingPeriod.h"

BillingPeriod::BillingPeriod(const QDate& startDate)
    : DbRecord(0)
{
	_status = NOT_OPENED;
	_startDate = startDate;
} 
BillingPeriod::~BillingPeriod()
{

}
BillingPeriod::BillingPeriod(const QDate& startDate,Status status)
    :DbRecord(0)
{
    _status = status;
    _startDate = startDate;
}
bool BillingPeriod::fetch()
{
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

        query->prepare("SELECT * FROM `billing_period` WHERE `id` = :id");
        int id = this->id();
        query->bindValue(":id",id);
        if(query->exec())
        {
            if(query->next())
            {
                _startDate = query->value(1).toDate();
                _status = (Status)query->value(2).toInt();
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
bool BillingPeriod::set()
{
    return false;
}
bool BillingPeriod::validate() const
{
    return false;
}
bool BillingPeriod::update() const
{
    return false;
}
int BillingPeriod::insert() const
{
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("INSERT INTO `billing_period` (start_date,status) VALUES(:start_date,:status");
        query->bindValue(":start_date",this->_startDate);
        query->bindValue(":phone_number",this->_status);
        if(query->exec())
        {
            query->prepare("SELECT id FROM `billing_period` WHERE `startDate` = :start_date");
            query->bindValue(":start_date",this->_startDate);
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
bool BillingPeriod::createDbTable()
{
    if(DbManager::manager().checkConnection()){
        QSqlQuery* query = DbManager::manager().makeQuery();
        if(query->exec("CREATE TABLE IF NOT EXISTS `billing_period` (`id` INT(11) NOT NULL AUTO_INCREMENT, `start_date` DATE, `status` INT(11), PRIMARY KEY(`id`))"))
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
void BillingPeriod::open()
{
	_status = OPEN;
}
void BillingPeriod::close()
{
	_status = CLOSED;
}
void BillingPeriod::set_modified()
{
	_status = MODIFIED;
}
