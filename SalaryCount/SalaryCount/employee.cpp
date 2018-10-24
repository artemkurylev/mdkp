#include "employee.h"

Employee::Employee()
    : DbRecord(0)
{
}
Employee::Employee(int id)
    : DbRecord(id)
{
}

Employee::~Employee()
{

}

