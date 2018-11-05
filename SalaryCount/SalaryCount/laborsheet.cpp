#include "laborsheet.h"

LaborSheet::LaborSheet(QObject *parent)
    : DbRecord(parent)
{

}
LaborSheet::LaborSheet(QObject *parent, int employeeId)
    : DbRecord(parent)
{
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
    int dutychart_index = bias;
	
	this->_grid.clear();
	// Заполнить табель отметками по умолчанию
    int month_length = this->_billingPeriod->startDate().daysInMonth();
    for(int i = 0; i < month_length; ++i,dutychart_index++)
    {
        if(dutychart_index >= length)
            dutychart_index = 0;
        Mark m(_dutyChart->grid()[dutychart_index]);
        this->_grid.push_back(m);
    }
	
	// Обновить табель в БД
    return this->update();
}
LaborSheet::~LaborSheet()
{

}

const Employee* LaborSheet::employee() const
{
	return NULL; // TODO: create from id & return
}

PayForm LaborSheet::payForm() const
{
	return employee()->hireDirective()->payForm();
}


int inline markMeasure(int mark_val, enum PayForm pay_form) 
{
	// для почасовой вернуть часы;
	// для помесячной - 1, если отметка ненулевая, иначе 0.
	return (pay_form == PER_HOUR)? (mark_val) : (mark_val > 0);
}

int LaborSheet::countDefaultTimeUnits() const
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
int LaborSheet::countActualTimeUnits () const
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
int LaborSheet::insert() const{
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("INSERT INTO `labor_sheet` (billing_period_id,employee_id,dutychart_id, closed) VALUES(:begin_date,:employee_id,:dutychart_id");
        query->bindValue(":begin_date",this->_billingPeriod->id());
        query->bindValue(":employee_id",this->_employeeId);
        query->bindValue(":dutychart_id", this->_dutyChart->id());
        if(query->exec())
        {
            for(int i = 0; i < this->_grid.length(); ++i)
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
bool LaborSheet::fetch(){
    return false;
}
bool LaborSheet::update() const{
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
            for(int i = 0; i < _grid.size(); ++i)
            {
                if(!_grid[i].update())
                {
                    //Ошибка!!!
                }
            }
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
bool LaborSheet::createDbTable() {
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