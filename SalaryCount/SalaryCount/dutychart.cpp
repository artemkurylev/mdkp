#include "dutychart.h"

void initalSetupForTableDutyChart();
DutyChart defaultChart();

DutyChart::DutyChart(int id)
    : DbRecord(id)
{
    //_id = id;
		/* DbRecord(id) performs: assign id, fetch. */
}
DutyChart::DutyChart(const QString& name, const QList<Mark>& marks,const QDate& anchorDate, enum PayForm payForm/*=PER_HOUR*/)	
{
    _grid = marks;
    _payForm=payForm;
    _name = name;
    _anchorDate = anchorDate;
}

DutyChart::DutyChart(int id, const QString& name, const QList<Mark>& marks,const QDate& anchorDate, enum PayForm payForm/*=PER_HOUR*/)
{
	_id = id;
	_grid = marks;
    _payForm=payForm;
    _name = name;
    _anchorDate = anchorDate;
}

bool DutyChart::createDbTable()
{
	bool success = false;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        if(query->exec("CREATE TABLE IF NOT EXISTS `dutychart` (`id` INT(11) NOT NULL AUTO_INCREMENT, `payform` INT(11), `anchor_date` DATE,`name` CHAR(10), PRIMARY KEY(`id`))"))
		{
            success = true;
			// позже это должно выполняться при создании предприятия
			initalSetupForTableDutyChart();
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
/*! Заполнить пустую таблицу начальными записями
	для успешного старта бизнес-процесса
*/
void initalSetupForTableDutyChart()
{
	if(BillingPeriod::countEntries() == 0)
	{
		// insert first rec
		DutyChart rec = defaultChart();
		rec.insert();
	}
}
int DutyChart::insert()
{
	int insert_id = -1;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("INSERT INTO `dutychart` (payform,anchor_date, name) VALUES(:payform,:anchor_date,:name)");
        query->bindValue(":payform",this->_payForm);
        query->bindValue(":anchor_date",this->_anchorDate);
        query->bindValue(":name",this->_name);
        if(query->exec())
        {
            if(query->exec("SELECT LAST_INSERT_ID()") && query->next())
            {   
                this->_id = query->value(0).toInt();
				insert_id = this->_id;
            }
            for(int i = 0; i < this->length(); ++i)
            {
                Mark mark(_grid[i].base(),_grid[i].altered(),_grid[i].countHours(),_grid[i].alteredCountHours(),this->_id);
                if(mark.insert() == -1)
                {
                    //Ошибка!!
                }
            }
        }
        else
        {
            //Ошибка!
            QString s = query->lastError().text();
            s+="as";
        }
        delete query;
    }
    return insert_id;
}
bool DutyChart::fetch()
{
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

        query->prepare("SELECT * FROM `dutychart` WHERE `id` = :id");
        int id = this->id();
        query->bindValue(":id",id);
        if(query->exec())
        {
            if(query->next())
            {
                _payForm = query->value(1).toInt();
                _anchorDate = query->value(2).toDate();
                _name = query->value(3).toString();
                QSqlQuery query_m = *(DbManager::manager().makeQuery());
                query_m.prepare("SELECT * FROM `mark` WHERE `dutychart_id` = :id");
                query_m.bindValue(":id", id);
                if(query_m.exec())
                {
                    while(query_m.next())
                    {
                        Mark m(query_m.value(1).toInt(),query_m.value(2).toInt(),query_m.value(3).toInt(),query_m.value(4).toInt(),query_m.value(5).toInt(),query_m.value(6).toInt());
                        _grid.append(m);
                    }
                    return true;
                }
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
    return false;
}
QMap<int,QString> DutyChart::getAll()
{
    QMap<int,QString> records;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

        query->prepare("SELECT id,name FROM `dutychart`");
        if(query->exec())
        {
            while(query->next())
            {
                records.insert(query->value(0).toInt(), query->value(1).toString()); 
            }
        }
        delete query;
    }

    return records;
}
long DutyChart::countEntries()
{
    int counter = 0;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

        query->prepare("SELECT COUNT(*) FROM `dutychart`");
        if(query->exec())
        {
            if(query->next())
                counter = query->value(0).toInt();
        }
        delete query;
    }
    return counter;
}
DutyChart::~DutyChart()
{

}

DutyChart defaultChart()
{
	// подготовить дату: прошедший ПН
	QDate monday = QDate::currentDate();
	monday.addDays( -(monday.dayOfWeek()-1) );

	QList<Mark> bmarks;

	for(int i=0; i<7; ++i)
	{
		//bmarks.append(Mark( /*!*/ ));
	}

	return DutyChart("5/2", bmarks, monday, PER_HOUR);
}