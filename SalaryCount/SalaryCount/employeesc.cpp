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
        //�������� ������
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
		// ������ ���� ������� ����� �������� DutyChart � LaborSheet (��-�� ������� ������)
        table_created = Mark::createDbTable();
        if(!table_created)
        {

        }
        
		// ����� ��� ������ ����������� ��� �������� �����������
		initalSetupForTableDutyChart();
    }
	else
	{
		//TODO
	}
}

Employee* EmployeeSC::shapeDataObject()
{
	return NULL;
}

void EmployeeSC::parseDataObject(Employee *obj)
{

}