#include "employeesc.h"

#include "dbmanager.h"
#include"qsqldatabase.h"

#include "unittest/DirectiveGeneratorTest.h"


EmployeeSC::EmployeeSC(QString dbName,Employee* employee, QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	this->journal = new log_errors();//������ ������ 

	initialDBManager(dbName);

	this->userData = employee;

	try
	{
		if(!this->userData->fetch()) throw this->journal->fetchError("�� ������� �������� ������ � ����������");
	}
	catch(log_errors::exception_states e)
	{
		QByteArray code = QString::number(this->journal->getLastErrorCode()).toLocal8Bit();
		QByteArray msg = this->journal->getLastError().toLocal8Bit();

		error_msg(code.data(),msg.data());//c������� �� ������
		this->journal->lastConflictNonResolved();
	}

}

EmployeeSC::~EmployeeSC()
{
	
}

void EmployeeSC::initialDBManager(QString dbName)
{
	DbManager& manager = DbManager::manager(dbName);
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

void EmployeeSC::error_msg(const char* short_description, const char* text)
{
	QTextCodec* c = QTextCodec::codecForLocale();
	QMessageBox::critical(NULL,c->toUnicode(short_description), c->toUnicode(text));
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
