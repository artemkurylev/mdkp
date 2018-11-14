#include "dutychart.h"

DutyChart::DutyChart(int id)
    : DbRecord(0)
{
    _id = id;
}
DutyChart::DutyChart(QString name, QList<Mark> marks, QDate anchorDate,enum PayForm payForm)	
{
    _grid = marks;
    _payForm=payForm;
    _name = name;
    _anchorDate = anchorDate;
}
bool DutyChart::createDbTable()
{
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        if(query->exec("CREATE TABLE IF NOT EXISTS `dutychart` (`id` INT(11) NOT NULL AUTO_INCREMENT, `payform` INT(11), `anchor_date` DATE,`name` CHAR(10), PRIMARY KEY(`id`))"))
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
        query->prepare("INSERT INTO `dutychart` (payform,anchor_date, name) VALUES(:payform,:anchor_date,:name");
        query->bindValue(":payform",this->_payForm);
        query->bindValue(":anchor_date",this->_anchorDate);
        query->bindValue(":name",this->_name);
        if(query->exec())
        {
            for(int i = 0; i < this->length(); ++i)
            {
                if(this->_grid[i].insert()== - 1)
                {
                    //Îøèáêà!!
                }
            }
            if(query->exec("SELECT LAST_INSERT_ID()") && query->next())
            {   
                return query->value(0).toInt();
            }
        }
        else
        {
            //Îøèáêà!
            QString s = query->lastError().text();
            s+="as";
            return -1;
        }
        delete query;
    }
    return -1;
}
bool DutyChart::fetch(){
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
                        Mark m(query_m.value(1).toInt(),query_m.value(2).toInt(),query_m.value(3).toInt(),query_m.value(4).toInt());
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
                records.insert(query->value(0).toInt(), query->value(0).toString()); 
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

//DutyChart DutyChart::baseObject()
//{
//	QList<Mark> bmarks;
//
//	for(int i=0; i<7; ++i)
//	{
//		bmarks.append(Mark());
//	}
//
//
//	DutyChart* obj = new
//}