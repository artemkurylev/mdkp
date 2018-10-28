#include "laborsheet.h"

LaborSheet::LaborSheet(QObject *parent)
    : DbRecord(parent)
{

}
LaborSheet::LaborSheet(QObject *parent, int employeeId)
    : DbRecord(parent)
{
    this->employeeId = employeeId;
}
bool LaborSheet::fillWithDefaults(){
    QDate buffer_date = this->_dutyChart->anchorDate();
    int count_diff_days = 0;
    count_diff_days = abs(buffer_date.daysTo(this->_beginDate));
    int bias = count_diff_days % this->_dutyChart->length();
    int length = _dutyChart->length();
    int month_length = this->_beginDate.daysInMonth();
    int dutychart_index = bias;
    for(int i = 0; i < month_length; ++i,dutychart_index++){
        if(dutychart_index >= length)
            dutychart_index = 0;
        Mark m(_dutyChart->grid()[dutychart_index]);
        this->_grid.push_back(m);
    }
    return this->update();
}
LaborSheet::~LaborSheet()
{

}


int LaborSheet::countDefaultTimeUnits() const
{
	return 0;
}
int LaborSheet::countActualTimeUnits () const
{
	return 0;
}

