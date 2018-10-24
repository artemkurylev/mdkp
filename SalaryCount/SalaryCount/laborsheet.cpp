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
    
    int count = 0;
    return false;
}
LaborSheet::~LaborSheet()
{

}
