#include "employeesc.h"

#include "dbmanager.h"
#include"qsqldatabase.h"

#include "unittest/DirectiveGeneratorTest.h"


EmployeeSC::EmployeeSC(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	//initialDBManager();
}

EmployeeSC::~EmployeeSC()
{
	
}

void EmployeeSC::initialDBManager()
{
	DbManager& manager = DbManager::manager();
    if(manager.checkConnection())
    {
        //Создание таблиц
        bool table_created = Employee::createDbTable();
        if(!table_created)
        {

        }
        table_created = BillingPeriod::createDbTable();
        if(!table_created)
        {

        }
        table_created = DutyChart::createDbTable();
        if(!table_created)
        {

        }
        table_created = LaborSheet::createDbTable();
        if(!table_created)
        {

        }
        table_created = HireDirective::createDbTable();
        if(!table_created)
        {

        }
		// должно быть вызвано после создания DutyChart и LaborSheet (из-за внешних ключей)
        table_created = Mark::createDbTable();
        if(!table_created)
        {

        }
        
		// позже это должно выполняться при создании предприятия
		initalSetupForTableDutyChart();
    }
	else
	{
		//TODO
	}
}

//Employee* EmployeeSC::shapeDataObject()
//{
//	return NULL;
//}
//
//void EmployeeSC::parseDataObject(Employee *obj)
//{
//
//}
//
//void EmployeeSC::updateInfo(QString name)
//{
//
//}
Employee* EmployeeSC::shapeDataObject()
{
	return NULL;
}

void EmployeeSC::parseDataObject(Employee *obj)
{

}

void EmployeeSC::updateInfo(QString name)
{

}
