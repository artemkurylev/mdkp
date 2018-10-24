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
    QDate date = this->_dutyChart->anchorDate(); 
    QDate buffer_date = this->_dutyChart->anchorDate();
    int count_diff_days = 0;
    count_diff_days = abs(buffer_date.daysTo(this->beginDate()));
    int bias = count_diff_days % this->_dutyChart->length();
    int length = _dutyChart->length();
    return false;
}
LaborSheet::~LaborSheet()
{

}
