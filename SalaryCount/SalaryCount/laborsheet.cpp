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
bool LaborSheet::fillWithDefaults(int empploeeId, QDate date,DutyChart* dutyChart){
    
    int count = 0;
    return false;
}
QList<Mark>* LaborSheet::getMarks(int empploeeId, QDate date){
    return &(this->grid);
}
LaborSheet::~LaborSheet()
{

}
