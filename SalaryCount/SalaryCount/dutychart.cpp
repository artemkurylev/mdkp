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
DutyChart::~DutyChart()
{

}
