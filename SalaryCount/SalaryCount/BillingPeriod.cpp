#include "BillingPeriod.h"

void initalSetupForTableBillingPeriod();

BillingPeriod::BillingPeriod(const QDate& startDate)
    : DbRecord()
{
	_status = NOT_OPENED;
	_startDate = startDate;
	_next = NULL;
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
BillingPeriod::BillingPeriod(const BillingPeriod& other)
{
    this->_status =  other._status;
    this->_startDate =  other._startDate;
}
BillingPeriod::~BillingPeriod()
{
	// free allocated record
	if(_next != NULL)
	{
		delete _next;
	}
}

bool BillingPeriod::fetch()
{
	bool success = false;
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
				//_startDate = QDate::fromString("yyyy-MM-dd", query->value(1).toString() );
                _status = (Status)query->value(2).toInt();
				success = false;
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
	bool success = false;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("UPDATE `billing_period` SET `start_date`=:start_date, `status`=:status WHERE  `id`=:id;");
        query->bindValue(":start_date",this->_startDate);
        query->bindValue(":status",this->_status);
        query->bindValue(":id",this->_id);
        if(query->exec())
        {
			success = true;
		}
        else
        {
            QString s = query->lastError().text();
            s+="as";
			s = query->executedQuery();
        }
        delete query;
    }
    else
	{
    }
    return success;
}
int BillingPeriod::insert()
{
	int insert_id = -1;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("INSERT INTO `billing_period` (start_date,status) VALUES(:start_date,:status)");
        query->bindValue(":start_date",this->_startDate);
        query->bindValue(":status",this->_status);
        if(query->exec())
        {
            //query->prepare("SELECT id FROM `billing_period` WHERE `start_date` = :start_date");
            //query->bindValue(":start_date",this->_startDate);
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
			s = query->executedQuery();
        }
        delete query;
    }
    else
	{
    }
	return insert_id;
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
			initalSetupForTableBillingPeriod();
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
void initalSetupForTableBillingPeriod()
{
	if(BillingPeriod::countEntries() == 0)
	{
		// insert first rec
        BillingPeriod bp(QDate(QDate::currentDate().year(),QDate::currentDate().month(), 1));
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
/*static*/ BillingPeriod* BillingPeriod::getByDate(const QDate& date)
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
/*static*/ long BillingPeriod::countEntries()
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

/*static*/ BillingPeriod* BillingPeriod::getCurrentPeriod()
{
	BillingPeriod* billing_period = NULL;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("SELECT * FROM billing_period WHERE status = :status");
        query->bindValue(":status",OPEN);
        if(query->exec() && query->next())
        {
            billing_period = new BillingPeriod(
				query->value(0).toInt(),
				query->value(1).toDate(),
				(BillingPeriod::Status)query->value(2).toInt()
				);
        }
        else
		{
            QString s = query->lastError().text();
            s+="as";
        }
		delete query;
    }
    return billing_period;
}

        query->prepare("SELECT * FROM `billing_period` WHERE start_date = :date");
        query->bindValue(":date",date);
        if(query->exec())
        {
            if(query->next())
            {
                BillingPeriod* period = new BillingPeriod(query->value(0).toInt(),query->value(1).toDate(),(BillingPeriod::Status)query->value(2).toInt());
                return period;
            }
        }
        delete query;
    }
    return NULL;
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

/*static*/ QPair<QDate,QDate> BillingPeriod::getDateSpan()
{
	QPair<QDate,QDate> span;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("SELECT MIN(start_date),MAX(start_date) FROM billing_period WHERE 1;");
        if(query->exec() && query->next())
        {
			span.first = query->value(0).toDate();
			span.second = query->value(1).toDate();
        }
        else
		{
            QString s = query->lastError().text();
            s+="as";
        }
		delete query;
    }
	
	return span;
}
