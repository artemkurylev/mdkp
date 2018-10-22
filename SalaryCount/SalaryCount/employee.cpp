#include "employee.h"

Employee::Employee(QObject *parent)
    : DbRecord(parent)
{
}
Employee::Employee(int id)
    : DbRecord(id)
{
}

Employee::~Employee()
{

}

