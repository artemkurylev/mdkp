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

