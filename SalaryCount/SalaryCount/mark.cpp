#include "mark.h"


Mark::Mark()
    : DbRecord()
{
	_base = INVALID;
	_altered = INVALID;
    _dutychartId = NULL;
    _laborsheetId = NULL;
    _countHours = 0;
    _alteredCountHours = 0;
} 

Mark::Mark(int id)
    : DbRecord(id)
{
	_base = INVALID;
	_altered = INVALID;
    _dutychartId = NULL;
    _laborsheetId = NULL;
    _countHours = 0;
    _alteredCountHours = 0;
} 

Mark::Mark(int dutychartId,int laborsheetId/*=NULL*/, int base/*=HOLIDAY*/, int altered/*=INVALID*/, int countHours/*=0*/, int alteredCountHours/*=-1*/)
    : DbRecord()
{
    _dutychartId = dutychartId;
    _laborsheetId = laborsheetId;
	_base = base;
	_altered = altered;
    _countHours = countHours;
    _alteredCountHours = alteredCountHours;
}

bool Mark::fetch()
{
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

        query->prepare("SELECT * FROM `mark` WHERE `id` = :id");
        int id = this->id();
        query->bindValue(":id",id);
        if(query->exec())
        {
            if(query->next())
            {
                _base = query->value(1).toInt();
                _altered = query->value(2).toInt();
                _dutychartId = query->value(3).toInt();
                _laborsheetId = query->value(4).toInt();
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
bool Mark::validate() const{
    return false;
}
bool Mark::set(){
    return false;
}

bool Mark::update() const
{
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("UPDATE `mark` SET base = :base , altered = :altered,count_hours= :count_hours, altered_count_hours = :altered_count_hours, WHERE id = :id");
        query->bindValue(":base",this->_base);
        query->bindValue(":altered",this->_altered);
        query->bindValue(":id", this->_id);
         query->bindValue(":count_hours",this->_countHours);
        query->bindValue(":altered_count_hours",this->_alteredCountHours);
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
int Mark::insert()
{
	int insert_id = -1;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("INSERT INTO `mark` (base,altered,count_hours,altered_count_hours,dutychart_id,laborsheet_id) VALUES(:base,:altered,:count_hours,:altered_count_hours,:dutychart_id,:laborsheet_id");
        query->bindValue(":base",this->_base);
        query->bindValue(":altered",this->_altered);
        query->bindValue(":count_hours",this->_countHours);
        query->bindValue(":altered_count_hours",this->_alteredCountHours);
        query->bindValue(":dutychart_id",this->_dutychartId);
        query->bindValue(":laborsheet_id",this->_laborsheetId);
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
        if(query->exec("CREATE TABLE IF NOT EXISTS `mark` (`id` INT(11) NOT NULL AUTO_INCREMENT, `base` INT(11), `altered` INT(11) ,`count_hours` INT(3),`altered_count_hours` INT(3),`dutychart_id` INT(11),`laborsheet_id` INT(11), PRIMARY KEY(`id`))"))
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
Mark::~Mark()
{

}
