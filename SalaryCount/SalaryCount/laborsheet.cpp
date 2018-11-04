#include "laborsheet.h"

LaborSheet::LaborSheet()
    : DbRecord(0)
{

}
LaborSheet::LaborSheet(int employeeId)
    : DbRecord(0)
{
    this->employeeId = employeeId;
}
bool LaborSheet::fillWithDefaults()
{
	// Вычислить относительное смещение наложения графика на месяц
    QDate buffer_date = this->_dutyChart->anchorDate();
    int count_diff_days = 0;
    count_diff_days = abs(buffer_date.daysTo(this->_beginDate));
    int length = _dutyChart->length();
    int bias = count_diff_days % length;
    int dutychart_index = bias;
	
	this->_grid.clear();
	// Заполнить табель отметками по умолчанию
    int month_length = this->_beginDate.daysInMonth();
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
    return -1;
}
bool LaborSheet::fetch(){
    return false;
}
bool LaborSheet::update() const{
    return false;
}
bool LaborSheet::createDbTable() {
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        if(query->exec("CREATE TABLE IF NOT EXISTS `labor_sheet` (`id` INT(11) NOT NULL AUTO_INCREMENT, `begin_date` DATE, `employee_id` INT(11),`dutychart_id` INT(11), PRIMARY KEY(`id`))"))
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