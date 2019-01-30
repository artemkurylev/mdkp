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

	if(getEmployeeData())
	{

	}
	else
	{
		//�������� ������ ���������� �����������
	}
}

EmployeeSC::~EmployeeSC()
{
	this->journal->~log_errors();
	this->userData->~Employee();
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

bool EmployeeSC::getEmployeeData()
{
	try
	{
		if(!this->userData->fetch()) throw this->journal->fetchError("�� ������� �������� ������ � ����������");

		HireDirective *hd = new HireDirective(this->userData->hireDirectiveID());
		if(hd->fetch()) throw this->journal->fetchError("parseDataObject hiredirective fetch error");

		DutyChart *userDutyChart = new DutyChart(this->userData->currentDutyChartID());
		if(userDutyChart->fetch()) throw this->journal->fetchError("parseDataObject hiredirective fetch error");

		parseBaseDataObject(hd,userDutyChart->name());

		return true;
	}
	catch(log_errors::exception_states e)
	{
		QByteArray code = QString::number(this->journal->getLastErrorCode()).toLocal8Bit();
		QByteArray msg = this->journal->getLastError().toLocal8Bit();

		error_msg(code.data(),msg.data());//c������� �� ������
		this->journal->lastConflictNonResolved();

		return false;
	}
}

void EmployeeSC::parseBaseDataObject(HireDirective *hd, QString dutyChartName)
{
	try
	{
		if(!this->userData) throw this->journal->nullPtr();

		ui.eFIO->setText(this->userData->fio());
		ui.eNumberPhone->setText(this->userData->phoneNumber());
		ui.INN->setText(QString::number(this->userData->inn()));

		ui.ePayFormChoice->setCurrentIndex(hd->payForm()==PER_MONTH ? 0 : 1);
		ui.eReceiptDate->setDate(hd->hireDate());
		ui.eOrderNum->setText(QString::number(hd->id()));
		ui.eSalary->setValue(hd->salary());

		ui.eDutyChart->setText(dutyChartName);
	}
	catch(log_errors::exception_states e)
	{

	}
}