#include "dutychart.h"

DutyChart::DutyChart(QObject *parent)
    : DbRecord(parent)
{
	// создать типичный график 5\2
	_grid.clear();
	_grid.reserve(7);
	for(int i=0 ; i<7 ; ++i )
	{
		if (i < 5)
			_grid.push_back(Mark::Type::USUAL);
		else
			_grid.push_back(Mark::Type::HOLIDAY);
	}
}
bool DutyChart::createDbTable()
{
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        if(query->exec("CREATE TABLE IF NOT EXISTS `dutychart` (`id` INT(11) NOT NULL AUTO_INCREMENT, `payform` INT(11), `anchor_date` DATE, PRIMARY KEY(`id`))"))
            return true;
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
int DutyChart::insert() const
{
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("INSERT INTO `dutychart` (payform,anchor_date) VALUES(:payform,:anchor_date");
        query->bindValue(":payform",this->_payForm);
        query->bindValue(":anchor_date",this->_anchorDate);
        if(query->exec())
        {
            for(int i = 0; i < this->length(); ++i)
            {
                if(this->_grid[i].insert()== - 1)
                {
                    //Ошибка!!
                }
            }
            if(query->exec("SELECT LAST_INSERT_ID()") && query->next())
                return query->value(0).toInt();
        }
        else
        {
            //Ошибка!
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
DutyChart::~DutyChart()
{

}
