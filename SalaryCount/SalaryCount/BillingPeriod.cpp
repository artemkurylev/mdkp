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

bool BillingPeriod::fetch()
{
    return false;
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
    return -1;
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
