#include "mark.h"

Mark::Mark()
    : DbRecord()
{
	_base = INVALID;
	_altered = INVALID;
    _dutyChartId = NULL;
    _laborsheetId = NULL;
    _countHours = 0;
    _alteredCountHours = -1;
}

Mark::Mark(const Mark &mark)
	: DbRecord()
{
	this->_id = mark.id();
	this->_base = mark.base();
	this->_altered = mark.altered();
	this->_dutyChartId = mark.dutyChartId();
	this->_laborsheetId = mark.laborsheetId();
	this->_countHours = mark.countHours();
	this->_alteredCountHours = mark.alteredCountHours();
}

//Mark::Mark(int id)
//    : DbRecord(id)
//{
//	_base = INVALID;
//	_altered = INVALID;
//    _dutyChartId = NULL;
//    _laborsheetId = NULL;
//    _countHours = 0;
//    _alteredCountHours = 0;
//}
Mark::Mark(int baseMark)
    : DbRecord()
{
	_base = baseMark;
	_altered = INVALID;
    _dutyChartId = NULL;
    _laborsheetId = NULL;
    _countHours = 0;
    _alteredCountHours = -1;

}
//Mark::Mark(int base, int altered, int countHours, int alteredCountHours, int dutyChartId,int laborsheetId)
//=======
//} 
Mark::Mark(int in_base, int in_altered, int in_countHours, int in_alteredCountHours, int in_dutyChartId /*= NULL*/,int in_laborsheetId /*= NULL*/)
    : DbRecord()
{
    _dutyChartId = in_dutyChartId;
    _laborsheetId = in_laborsheetId;
	_base = in_base;
	_altered = in_altered;
    _countHours = in_countHours;
    _alteredCountHours = in_alteredCountHours;
}
Mark::~Mark()
{

}

bool Mark::fetch()
{
	bool success = false;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

		// CREATE TABLE IF NOT EXISTS `mark` (`id` INT(11) NOT NULL AUTO_INCREMENT, `base` INT(11), `altered` INT(11) ,`count_hours` INT(3),`altered_count_hours` INT(3),`dutychart_id` INT(11),`laborsheet_id` INT(11), PRIMARY KEY(`id`))
        query->prepare("SELECT * FROM `mark` WHERE `id` = :id");
        int id = this->id();
        query->bindValue(":id",id);
        if(query->exec())
        {
            if(query->next())
            {
                _base = query->value(1).toInt();
                _altered = query->value(2).toInt();
                _countHours = query->value(3).toInt();
                _alteredCountHours = query->value(4).toInt();
                _dutyChartId = query->value(5).toInt();
                _laborsheetId = query->value(6).toInt();
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
    else
    {
    }
    return success;
}
bool Mark::validate() const
{
    return false;
}
bool Mark::update() const
{
	bool success = false;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("UPDATE `mark` SET `base` = :base , `altered` = :altered,`count_hours`= :count_hours, `altered_count_hours` = :altered_count_hours WHERE `id` = :id");
        query->bindValue(":base",this->_base);
        query->bindValue(":altered",this->_altered);
        query->bindValue(":id", this->_id);
        query->bindValue(":count_hours",this->_countHours);
        query->bindValue(":altered_count_hours",this->_alteredCountHours);
        if(query->exec())
        {
            success = true;
        }
        else
        {
            QString s = query->lastError().text();
            delete query;
            return false;
        }
        delete query;
    }
    return success;
}
int Mark::insert()
{
	int insert_id = -1;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
		if(this->_laborsheetId == 0)
		{
			query->prepare("INSERT INTO `mark` (base,altered,count_hours,altered_count_hours,dutychart_id) VALUES(:base,:altered,:count_hours,:altered_count_hours,:dutychart_id)");
			query->bindValue(":dutychart_id",this->_dutyChartId);
		}
		else
		{
			query->prepare("INSERT INTO `mark` (base,altered,count_hours,altered_count_hours,laborsheet_id) VALUES(:base,:altered,:count_hours,:altered_count_hours,:laborsheet_id)");
			query->bindValue(":laborsheet_id",this->_laborsheetId);
		}
		query->bindValue(":base",this->_base);
        query->bindValue(":altered",this->_altered);
        query->bindValue(":count_hours",this->_countHours);
        query->bindValue(":altered_count_hours",this->_alteredCountHours);
        if(query->exec())
        {
            if(query->exec("SELECT LAST_INSERT_ID()") && query->next())
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
    else
    {
    }
	return insert_id;
}
bool Mark::createDbTable()
{
	bool success = false;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        if(query->exec("CREATE TABLE IF NOT EXISTS `mark` (`id` INT(11) NOT NULL AUTO_INCREMENT, `base` INT(11), `altered` INT(11) ,`count_hours` INT(3),`altered_count_hours` INT(3),`dutychart_id` INT(11) NULL,`laborsheet_id` INT(11) NULL, PRIMARY KEY(`id`),	CONSTRAINT `FK_mark_dutychart` FOREIGN KEY (`dutychart_id`) REFERENCES `dutychart` (`id`) ON DELETE CASCADE,	CONSTRAINT `FK_mark_labor_sheet` FOREIGN KEY (`laborsheet_id`) REFERENCES `labor_sheet` (`id`) ON DELETE CASCADE )"))
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
void Mark::commitChanges()
{
	if(isAltered())
	{
		_base = _altered;
	}
	if(isAlteredCountHours())
	{
		_countHours = _alteredCountHours;
	}
	resetAltered();
}
