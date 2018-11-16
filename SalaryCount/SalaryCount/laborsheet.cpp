#include "laborsheet.h"


LaborSheet::LaborSheet()
    : DbRecord()
{
    _billingPeriod = NULL;
    _employee = NULL;
    _dutyChart = NULL;
}

LaborSheet::LaborSheet(int employeeId)
    : DbRecord()
{
    _billingPeriod = NULL;
    _employee = NULL;
    _dutyChart = NULL;
    this->_employeeId = employeeId;
}
bool LaborSheet::fillWithDefaults()
{
	// Вычислить относительное смещение наложения графика на месяц
    QDate buffer_date = this->_dutyChart->anchorDate();
    int count_diff_days = 0;
    count_diff_days = abs(buffer_date.daysTo(this->_billingPeriod->startDate()));
    int length = _dutyChart->length();
    int bias = count_diff_days % length;
    int dutyChart_index = bias;
	
	this->_grid.clear();
	// Заполнить табель отметками по умолчанию
    int month_length = this->_billingPeriod->startDate().daysInMonth();
    for(int i = 0; i < month_length; ++i,dutyChart_index++)
    {
        if(dutyChart_index >= length)
            dutyChart_index = 0;
        Mark m(_dutyChart->grid()[dutyChart_index]);
        this->_grid.push_back(m);
    }
	
	// Обновить табель в БД
    return this->update();
}
LaborSheet::~LaborSheet()
{
	// free allocated record
	if(_employee != NULL)
	{
		delete _employee;
	}
	if(_billingPeriod != NULL)
	{
		delete _billingPeriod;
	}
	if(_dutyChart != NULL)
	{
		throw("Всё-таки он оказался кому-то нужен?!");
		delete _dutyChart;
	}
}

Employee* LaborSheet::employee()
{
	if(_employee == NULL)
	{
		_employee = new Employee(_employeeId);
	}
	return _employee;
}
BillingPeriod* LaborSheet::billingPeriod()
{
	if(_billingPeriod == NULL)
	{
		_billingPeriod = new BillingPeriod(_billingPeriodId);
	}
	return _billingPeriod;
}
PayForm LaborSheet::payForm()
{
	Employee* e = employee();
	HireDirective* h = e->hireDirective();
	PayForm p = h->payForm();

	//delete e;
	delete h;

	return p;
}


int inline markMeasure(int mark_val, enum PayForm pay_form) 
{
	// для почасовой вернуть часы;
	// для помесячной - 1, если отметка ненулевая, иначе 0.
	return (pay_form == PER_HOUR)? (mark_val) : (mark_val > 0);
}

int LaborSheet::countDefaultTimeUnits()
{
	int total = 0;
	enum PayForm pay_form;
	pay_form = payForm();

	foreach(Mark mark , this->marks())
	{
		total += markMeasure(mark.base(), pay_form);
	}

	return total;
}
int LaborSheet::countActualTimeUnits()
{
	int total = 0;
	enum PayForm pay_form;
	pay_form = payForm();

	foreach(Mark mark , this->marks())
	{
		total += markMeasure(mark.altered(), pay_form);
	}

	return total;
}
bool LaborSheet::validate() const{
    return false;
}
int LaborSheet::insert()
{
	int insert_id = -1;
	if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("INSERT INTO `labor_sheet` (billing_period_id,employee_id,dutychart_id, closed) VALUES(:billing_period_id,:employee_id,:dutychart_id");
        query->bindValue(":billing_period_id",this->_billingPeriod->id());
        query->bindValue(":employee_id",this->_employeeId);
        query->bindValue(":dutychart_id", this->_dutyChart->id());

        if(query->exec())
        {
            if(query->exec("SELECT LAST_INSERT_ID()") && query->next())
			{
				this->_id = query->value(0).toInt();
                insert_id = this->_id;
			}
			// создать все отметки в БД
            for(int i = 0; i < this->_grid.length(); ++i)
            {
				// записать ID в отметку!
				this->_grid[i].setLaborsheetId(this->_id);

                if(this->_grid[i].insert()== - 1)
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
    else
	{
    }
	return insert_id;
}
bool LaborSheet::update() const
{
	bool success = false;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("UPDATE `labor_sheet` SET billing_period_id = :billing_period_id , employee_id = :employee_id, dutychart_id = :dutychart_id WHERE `id` =:id");
        query->bindValue(":billing_period_id",this->_billingPeriod->id());
        query->bindValue(":employee_id",this->_employeeId);
        query->bindValue(":dutychart_id",this->_dutyChart->id());
        query->bindValue(":id",this->id());
        if(query->exec())
        {
            success = true;
            for(int i = 0; i < _grid.size(); ++i)
            {
                if(!_grid[i].update())
                {
                    //Ошибка!!!
			        success = false;
                }
            }
        }
        else
        {
        }
        delete query;
    }
    return success;
}
bool LaborSheet::createDbTable()
{
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        if(query->exec("CREATE TABLE IF NOT EXISTS `labor_sheet` (`id` INT(11) NOT NULL AUTO_INCREMENT, `billing_period_id` INT(11), `employee_id` INT(11),`dutychart_id` INT(11), PRIMARY KEY(`id`))"))
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
QMap <int, int> LaborSheet::getAll()
{
    QMap <int, int> result;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        if(query->exec("SELECT id,employee_id FROM `labor_sheet`"))
        {
            while(query->next())
            {
                result.insert(query->value(0).toInt(),query->value(1).toInt());
            }
        }
    }
    return result;
}
bool LaborSheet::fetch()
{
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

        query->prepare("SELECT * FROM `labor_sheet` WHERE `id` = :id");
        int id = this->id();
        query->bindValue(":id",id);
        if(query->exec())
        {
            if(query->next())
            {
				// получить ID сотрудника
                this->_employeeId = query->value(2).toInt();

				// получить ID периода
                this->_employeeId = query->value(1).toInt();
				
				// получить ID графика
                this->_dutyChartId = query->value(3).toInt();

     //           QSqlQuery query_b = *(DbManager::manager().makeQuery());
     //           query_b.prepare("SELECT * FROM `billing_period` WHERE `id` = :billing_period_id");
     //           query_b.bindValue(":billing_period_id",query->value(1).toInt());
     //           if(query->exec() && query->next())
     //           {
					//this->_billingPeriodId = 
     //               BillingPeriod* period = new BillingPeriod(query->value(1).toDate(),(BillingPeriod::Status)query->value(2).toInt());
     //               this->_billingPeriod = period;
     //           }
     //           if(query->exec() && query->next())
     //           {
     //               DutyChart* dutyChart = new DutyChart(query->value(3).toInt());
     //               this->_dutyChart = dutyChart;
     //			  }

                QSqlQuery* query_m = DbManager::manager().makeQuery();
                query_m->prepare("SELECT * FROM `mark` WHERE `laborsheet_id` = :id");
                query_m->bindValue(":id", id);
                if(query_m->exec())
                {
                    while(query_m->next())
                    {
                        Mark m(query_m->value(1).toInt(),
							query_m->value(2).toInt(),
							query_m->value(3).toInt(),
							query_m->value(4).toInt(),
							query->value(5).toInt(),
							query->value(6).toInt()
							);
                        _grid.append(m);
                    }
                }
				delete query_m;
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
long LaborSheet::countEntries()
{
    int counter = 0;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

        query->prepare("SELECT COUNT(*) FROM `labor_sheet`");
        if(query->exec())
        {
            if(query->next())
                counter = query->value(0).toInt();
        }
        delete query;
    }
    return counter;
}