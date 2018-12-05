#include "employee.h"

Employee::Employee()
    : DbRecord()
{
	throw("it`s wrong constructor!");
	_hireDirective = NULL;
}
Employee::Employee(int id)
    : DbRecord(id)
{
	_hireDirective = NULL;
    _nextDutyChartID = -1;
}
Employee::Employee(const Employee& employee)
{
    this->_id = employee.id();
    this->_fio = employee.fio();
    this->_phoneNumber = employee.phoneNumber();
    this->_currentDutyChartID = employee.currentDutyChartID();
    this->_hireDirectiveID = employee.hireDirectiveID();
    this->_nextDutyChartID = employee.nextDutyChartID();
    this->_nextDutyChartSince = employee.nextDutyChartSince();
    this->_hireDirective = NULL;
    _nextDutyChartID= - 1;
}
/*! Конструктор создания новой записи
Предполагается, что приказ и график уже созданы и имеют ID
*/

Employee::Employee(QString _fio,QString _phoneNumber,long long _INN,int _currentDutyChartID,int _hireDirectiveID)
{
	this->_fio = _fio;
	this->_phoneNumber = _phoneNumber;
	this->_INN = _INN;
	this->_currentDutyChartID = _currentDutyChartID;
	this->_hireDirectiveID = _hireDirectiveID;
    this->_hireDirective = NULL;
	// оставить пустыми
    _nextDutyChartID = - 1;
	resetNextDutyChart();
}
Employee::Employee(int id, QString _fio,QString _phoneNumber,long long _INN,int _currentDutyChartID,int _hireDirectiveID)
{
    this->_id = id;
	this->_fio = _fio;
	this->_phoneNumber = _phoneNumber;
	this->_INN = _INN;
	this->_currentDutyChartID = _currentDutyChartID;
	this->_hireDirectiveID = _hireDirectiveID;
    this->_hireDirective = NULL;
    _nextDutyChartID = -1;
	// оставить пустыми
	resetNextDutyChart();
}
Employee::~Employee()
{
	// free allocated record
	if(_hireDirective != NULL)
	{
		delete _hireDirective;
	}
}

bool Employee::update() const
{
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("UPDATE `employee` SET `fio` = :fio , `phone_number` = :phone_number, `inn` = :inn, `hire_directive_id` = :hire_directive_id, `dutychart_id` = :dutychart_id, `next_dutychart_id` = :next_dutychart_id, `next_dutychart_since` = :next_dutychart_since WHERE `id` = :id");
        query->bindValue(":fio",this->_fio);
        query->bindValue(":phone_number",this->_phoneNumber);
        query->bindValue(":inn",this->_INN);
        query->bindValue(":hire_directive_id",this->_hireDirectiveID);
        query->bindValue(":dutychart_id",this->_currentDutyChartID);
        query->bindValue(":next_dutychart_id",this->_nextDutyChartID);
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
	bool success = false;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        if(query->exec("CREATE TABLE IF NOT EXISTS `employee` (`id` INT(11) NOT NULL AUTO_INCREMENT, `fio` CHAR(30) NOT NULL, `phone_number` CHAR(20),`inn` DECIMAL(12),`hire_directive_id` INT(11),`dutychart_id` INT(11),`next_dutychart_id` INT(11),`next_dutychart_since` DATE, PRIMARY KEY(`id`))"))
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
bool Employee::fetch()
{
	bool success = false;
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
                _hireDirectiveID = query->value(4).toLongLong();
                _currentDutyChartID = query->value(5).toInt();
                _nextDutyChartID = query->value(6).toInt();
                _nextDutyChartSince = query->value(7).toDate();
                _hireDirective=NULL;
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
int Employee::insert()
{
	int insert_id = -1;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("INSERT INTO `employee` (`fio`,`phone_number`,`inn`,`hire_directive_id`,`dutychart_id`) VALUES(:fio,:phone_number,:inn,:hire_directive_id,:dutychart_id);");
        query->bindValue(":fio",this->_fio);
        query->bindValue(":phone_number",this->_phoneNumber);
        query->bindValue(":inn",this->_INN);
        query->bindValue(":hire_directive_id",this->_hireDirectiveID);
        query->bindValue(":dutychart_id",this->_currentDutyChartID);
        if(query->exec())
        {
            query->prepare("SELECT id FROM `employee` WHERE `inn` = :inn");
            query->bindValue(":inn",this->_INN);
            if(query->exec() && query->next())
			{
                this->_id = query->value(0).toInt();
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
    else{
    }
	return insert_id;
}
QMap<int,QString> Employee::getAll()
{
    QMap<int,QString> records;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

        query->prepare("SELECT `id`,`fio` FROM `employee`");
        if(query->exec())
        {
            while(query->next())
            {
                int id = query->value(0).toInt();
                QString s = query->value(1).toString();
                records[id] = s; 
            }
        }
        QString s = query->lastError().text();
        delete query;
    }

    return records;
}
bool Employee::validate() const
{
    /*Возвращать неверное поле и сообщение об ощибке*/
	bool success = false;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("SELECT id FROM `employee` WHERE `id` <> :id AND ( `phone_number` = :phone_number OR `inn` = :inn );");
        query->bindValue(":id",this->_id);
        query->bindValue(":phone_number",this->_phoneNumber);
        query->bindValue(":inn",this->_INN);
        if(query->exec())
        {
            if( ! query->next()) // нет ни одной конфликтующей записи
			{
				success = true;
			}
			else
			{
				// извлечь конфликтующие записи
				// и отправить их куда следует (через сигнал/слот?)
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
long Employee::countEntries()
{
    int counter = 0;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

        query->prepare("SELECT COUNT(*) FROM `employee`");
        if(query->exec())
        {
            if(query->next())
                counter = query->value(0).toInt();
        }
        delete query;
    }
    return counter;
}


HireDirective * Employee::hireDirective()
{
	if(_hireDirective == NULL)
	{
		_hireDirective = new HireDirective(_hireDirectiveID);
        _hireDirective->fetch();
	}
	return _hireDirective;
}

bool Employee::applyDutyChartChange(const QDate& currentPeriodStart)
{
	bool reset = false
		,is_date = this->_nextDutyChartSince.isValid()
		,is_id = this->_nextDutyChartID >= 1;

	if(is_date != is_id)
	{
		// невалидное состояние столбцов
		reset = true;
	}
	else if(is_date && is_id && this->_nextDutyChartSince <= currentPeriodStart)
	{
		// назначение есть и время пришло
		this->_currentDutyChartID = this->_nextDutyChartID;
		reset = true;
	}

	if(reset)
	{
		resetNextDutyChart();
	}
	return reset;
}
