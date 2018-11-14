#include "BillingPeriod.h"

void initalSetupForTable();

BillingPeriod::BillingPeriod(const QDate& startDate)
    : DbRecord()
{
	_status = NOT_OPENED;
	_startDate = startDate;
	_next = NULL;
}
BillingPeriod::~BillingPeriod()
{
	// free allocated record
	if(_next != NULL)
	{
		delete _next;
	}
}
BillingPeriod::BillingPeriod(const QDate& startDate,Status status)
    :DbRecord()
{
    _status = status;
    _startDate = startDate;
	_next = NULL;
}
BillingPeriod::BillingPeriod(int id, const QDate& startDate,Status status)
    :DbRecord(/*id!*/)
{
    _id = id;
    _status = status;
    _startDate = startDate;
	_next = NULL;
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
int BillingPeriod::insert()
{
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("INSERT INTO `billing_period` (start_date,status) VALUES(:start_date,:status)");
        query->bindValue(":start_date",this->_startDate);
        query->bindValue(":status",this->_status);
        if(query->exec())
        {
            query->prepare("SELECT id FROM `billing_period` WHERE `start_date` = :start_date");
            query->bindValue(":start_date",this->_startDate);
            if(query->exec() && query->next())
                this->_id = query->value(0).toInt();
                return this->_id;
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
	bool success = false;
    if(DbManager::manager().checkConnection())
	{
        QSqlQuery* query = DbManager::manager().makeQuery();
        if(query->exec("CREATE TABLE IF NOT EXISTS `billing_period` (`id` INT(11) NOT NULL AUTO_INCREMENT, `start_date` DATE, `status` INT(11), PRIMARY KEY(`id`))"))
		{
            success = true;
			// позже это должно выполняться при создании предприятия
			initalSetupForTable();
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
        success = false;
    }
    return success;
}
/*! Заполнить пустую таблицу начальными записями
	для успешного старта бизнес-процесса
*/
void initalSetupForTable()
{
	if(BillingPeriod::countEntries() == 0)
	{
		// insert first rec
		BillingPeriod bp(QDate(2000,1,1));
		bp.open();
		bp.insert();
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
BillingPeriod* BillingPeriod::getByDate(const QDate& date)
{
	BillingPeriod* billing_period = NULL;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("SELECT * FROM billing_period WHERE start_date = :start_date");
        query->bindValue(":start_date",date);
        if(query->exec() && query->next())
        {
            billing_period = new BillingPeriod(query->value(0).toInt(),query->value(1).toDate(),(BillingPeriod::Status)query->value(2).toInt());
        }
		delete query;
    }
    return billing_period;
}
long BillingPeriod::countEntries()
{
    int counter = 0;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

        query->prepare("SELECT COUNT(*) FROM `billing_period`");
        if(query->exec())
        {
            if(query->next())
                counter = query->value(0).toInt();
        }
        delete query;
    }
    return counter;
}

// Получить/создать следующий расчётный период
BillingPeriod* BillingPeriod::nextPeriod()
{
	if(_next == NULL)
	{
		QDate next_month_date =  startDate().addMonths(1);
		_next = BillingPeriod::getByDate(next_month_date);
		if(_next == NULL)
		{
			_next = new BillingPeriod(next_month_date);
			_next->insert();
		}
	}
	return _next;
}
