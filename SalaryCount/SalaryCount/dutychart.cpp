#include "dutychart.h"

void initalSetupForTableDutyChart();
DutyChart defaultChart();
DutyChart defaultChart2();

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
			// ����� ��� ������ ����������� ��� �������� �����������
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
/*! ��������� ������ ������� ���������� ��������
	��� ��������� ������ ������-��������
*/
void initalSetupForTableDutyChart()
{
	if(DutyChart::countEntries() == 0)
	{
		// insert first rec
		DutyChart rec = defaultChart();
		rec.insert();
		rec = defaultChart2();
		rec.insert();
	}
}
bool DutyChart::validate() const
{
	return _name.size() <= 10 && true;
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
				// �������� ID � �������!
				this->_grid[i].setDutyChartId(this->_id);

                if(this->_grid[i].insert() == -1)
                {
                    //������!!
		            QString s; // = query->lastError().text();
		            s+="as";
               }
            }
        }
        else
        {
            //������!
            QString s = query->lastError().text();
            s+="as";
        }
        delete query;
    }
    return insert_id;
}
bool DutyChart::update() const
{
    bool success = false;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("UPDATE `dutychart` SET payform = :payform , anchor_date = :anchor_date, name= :name WHERE id = :id");
        query->bindValue(":payform",this->_payForm);
        query->bindValue(":anchor_date",this->_anchorDate);
        query->bindValue(":name", this->_name);
        query->bindValue(":id",this->_id);
        if(query->exec())
        {
            bool success_mark = true;
            for(int i = 0; i < this->_grid.size(); ++i)
			{
                if(!_grid[i].update())
                    success_mark = false;
            }
            success = success_mark;
        }
    }
    return success;
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
                query_m.prepare("SELECT * FROM `mark` WHERE `dutychart_id` = :id ORDER BY `id`");
                query_m.bindValue(":id", id);
                if(query_m.exec())
                {
                    while(query_m.next())
                    {
                        Mark m(query_m.value(1).toInt(),query_m.value(2).toInt(),query_m.value(3).toInt(),query_m.value(4).toInt(),query_m.value(5).toInt(),query_m.value(6).toInt());
                        int x =query_m.value(0).toInt();
						m.setId(x);
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

        query->prepare("SELECT `id`,`name` FROM `dutychart`");
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
	// ����������� ����: ��������� ��
	QDate monday = QDate::currentDate();
	monday = monday.addDays( -(monday.dayOfWeek()-1) );

	QList<Mark> bmarks;

	for(int i=0; i<7; ++i)
	{
		int base = i<5? Mark::ATTENDS : Mark::HOLIDAY;
		int countHours = i<5? Mark::USUAL : 0;
		bmarks.append(Mark(base, Mark::INVALID, countHours, -1, NULL,NULL));
	}

	return DutyChart("5/2", bmarks, monday, PER_HOUR);
}
DutyChart defaultChart2()
{
	// ����������� ����: ��������� ��
	QDate monday = QDate::currentDate();
	monday = monday.addDays( -(monday.dayOfWeek()-1) );

	QList<Mark> bmarks;

	bmarks.append(Mark(Mark::ATTENDS, Mark::INVALID, 0, -1, NULL,NULL));
	bmarks.append(Mark(Mark::ATTENDS, Mark::INVALID, 0, -1, NULL,NULL));
	bmarks.append(Mark(Mark::HOLIDAY, Mark::INVALID, 0, -1, NULL,NULL));
	bmarks.append(Mark(Mark::HOLIDAY, Mark::INVALID, 0, -1, NULL,NULL));
	bmarks.append(Mark(Mark::ATTENDS, Mark::INVALID, 0, -1, NULL,NULL));
	bmarks.append(Mark(Mark::ATTENDS, Mark::INVALID, 0, -1, NULL,NULL));
	bmarks.append(Mark(Mark::HOLIDAY, Mark::INVALID, 0, -1, NULL,NULL));

	return DutyChart("2/2/2/1", bmarks, monday, PER_MONTH);
}
QMap<int,QString> DutyChart::getAllByPayForm(PayForm payform)
{
    QMap<int,QString> records;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

        query->prepare("SELECT `id`,`name` FROM `dutychart` WHERE `payform` = :payform");
        query->bindValue(":payform", payform);
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