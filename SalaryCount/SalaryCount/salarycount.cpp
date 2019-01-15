#include "salarycount.h"

#include <QtTest/QtTest>
#include "dbmanager.h"
#include"dutychart.h"
#include"qsqldatabase.h"

#include "unittest/DirectiveGeneratorTest.h"


SalaryCount::SalaryCount(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	initialDBManager();

	// test>
	//BillingPeriod* bp = BillingPeriod::getCurrentPeriod();
	//for(int i=0 ; i<3 ; ++i)
	//{
	//	BookKeeper::closeBillingPeriod(*bp);
	//	bp = bp->nextPeriod();
	//}
	// <test

	this->editState = false;
	
	//// ������ ������������
	DirectiveGeneratorTest dir_gen_test(0);
	QTest::qExec( &dir_gen_test , NULL , NULL);

	//���������� �� ��������� �������� ��������
	this->dutyChart = new salarycountDutyChart(&this->ui,ui.DutyCharAction->whatsThis());
	connect(this, SIGNAL(showPaget(QString)),this->dutyChart,SLOT(updateInfo(QString)));//�������� ���������� �� ��������
	connect(this->dutyChart,SIGNAL(changeState(bool)),this,SLOT(rememberState(bool)));//�� �������� ����� ���� ��� ������: �������� � ��������� �������
	connect(this,SIGNAL(saveChanges()),this->dutyChart,SLOT(saveNewDutyChart()));//���������� �������� ������ �� ���������� ��������
	connect(this,SIGNAL(cancelChanges()),this->dutyChart,SLOT(cancelNewDutyChart()));//���������� �������� ������ ������ ��������������

	//���������� �� ��������� ��������� �����
	this->employees = new salarycountEmployees(&this->ui,ui.EmployeeListAction->whatsThis());
	connect(this, SIGNAL(showPaget(QString)),this->employees,SLOT(updateInfo(QString)));//�������� ���������� �� ��������
	connect(this->employees,SIGNAL(changeState(bool)),this,SLOT(rememberState(bool)));//�� �������� ����� ���� ��� ������: �������� � ��������� �������
	connect(this,SIGNAL(saveChanges()),this->employees,SLOT(saveNewEmployee()));//���������� �������� ������ �� ���������� ��������
	connect(this,SIGNAL(cancelChanges()),this->dutyChart,SLOT(cancelNewEmployee()));//���������� �������� ������ ������ ��������������
	
    //����������� �� ��������� �������
    this->laborSheet = new salarycountLaborSheet(&this->ui,ui.LaborSheetAction->whatsThis());
	connect(this, SIGNAL(showPaget(QString)),this->laborSheet,SLOT(updateInfo(QString)));//�������� ���������� �� ��������
    //���������� �� ��������� ��������
    this->directives = new salarycountDirectives(&this->ui,ui.HireDirectiveAction->whatsThis());
    connect(this, SIGNAL(showPaget(QString)),this->directives,SLOT(updateInfo(QString)));
	//TODO

	ui.saveDutyChartBtn->setEnabled(true);
	ui.cancelDutyChartBtn->setEnabled(true);

	//������������ �������
	ui.stackedWidget->setCurrentIndex(2);//������������ ��������� �� �������� � ������������
	this->currentAction = ui.DutyCharAction;
	this->currentAction->setEnabled(false);

	connect(ui.CompanyMenu,SIGNAL(triggered(QAction*)), this,SLOT(showPage(QAction*)));

	connect(ui.FileMenu,SIGNAL(triggered(QAction*)), this,SLOT(showCompanyDialog(QAction*)));

	connect(ui.ExitAction,SIGNAL(triggered()), this,SLOT(close()));

	showPage(ui.DutyCharAction);
}
SalaryCount::SalaryCount(QString dbName, QWidget *parent)
    : QMainWindow()
{
    ui.setupUi(this);

	initialDBManager(dbName);

	// test>
	//BillingPeriod* bp = BillingPeriod::getCurrentPeriod();
	//for(int i=0 ; i<3 ; ++i)
	//{
	//	BookKeeper::closeBillingPeriod(*bp);
	//	bp = bp->nextPeriod();
	//}
	// <test

	this->editState = false;
	
	//// ������ ������������
	DirectiveGeneratorTest dir_gen_test(0);
	QTest::qExec( &dir_gen_test , NULL , NULL);

	//���������� �� ��������� �������� ��������
	this->dutyChart = new salarycountDutyChart(&this->ui,ui.DutyCharAction->whatsThis());
	connect(this, SIGNAL(showPaget(QString)),this->dutyChart,SLOT(updateInfo(QString)));//�������� ���������� �� ��������
	connect(this->dutyChart,SIGNAL(changeState(bool)),this,SLOT(rememberState(bool)));//�� �������� ����� ���� ��� ������: �������� � ��������� �������
	connect(this,SIGNAL(saveChanges()),this->dutyChart,SLOT(saveNewDutyChart()));//���������� �������� ������ �� ���������� ��������
	connect(this,SIGNAL(cancelChanges()),this->dutyChart,SLOT(cancelNewDutyChart()));//���������� �������� ������ ������ ��������������

	//���������� �� ��������� ��������� �����
	this->employees = new salarycountEmployees(&this->ui,ui.EmployeeListAction->whatsThis());
	connect(this, SIGNAL(showPaget(QString)),this->employees,SLOT(updateInfo(QString)));//�������� ���������� �� ��������
	connect(this->employees,SIGNAL(changeState(bool)),this,SLOT(rememberState(bool)));//�� �������� ����� ���� ��� ������: �������� � ��������� �������
	connect(this,SIGNAL(saveChanges()),this->employees,SLOT(saveNewEmployee()));//���������� �������� ������ �� ���������� ��������
	connect(this,SIGNAL(cancelChanges()),this->dutyChart,SLOT(cancelNewEmployee()));//���������� �������� ������ ������ ��������������
	
    //����������� �� ��������� �������
    this->laborSheet = new salarycountLaborSheet(&this->ui,ui.LaborSheetAction->whatsThis());
	connect(this, SIGNAL(showPaget(QString)),this->laborSheet,SLOT(updateInfo(QString)));//�������� ���������� �� ��������
    //���������� �� ��������� ��������
    this->directives = new salarycountDirectives(&this->ui,ui.HireDirectiveAction->whatsThis());
    connect(this, SIGNAL(showPaget(QString)),this->directives,SLOT(updateInfo(QString)));
	//TODO

	ui.saveDutyChartBtn->setEnabled(true);
	ui.cancelDutyChartBtn->setEnabled(true);

	//������������ �������
	ui.stackedWidget->setCurrentIndex(2);//������������ ��������� �� �������� � ������������
	this->currentAction = ui.DutyCharAction;
	this->currentAction->setEnabled(false);

	connect(ui.CompanyMenu,SIGNAL(triggered(QAction*)), this,SLOT(showPage(QAction*)));

	connect(ui.FileMenu,SIGNAL(triggered(QAction*)), this,SLOT(showCompanyDialog(QAction*)));

	connect(ui.ExitAction,SIGNAL(triggered()), this,SLOT(close()));

	showPage(ui.DutyCharAction);
}
SalaryCount::~SalaryCount()
{
	delete this->dutyChart;
}

void SalaryCount::initialDBManager()
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

	//return??
}
void SalaryCount::initialDBManager(QString dbName)
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

//! �������� ������ �� �������� ���� ����������� ��������
bool SalaryCount::isEditable()
{
	if(this->editState)
	{
		QTextCodec* c = QTextCodec::codecForLocale();
		QMessageBox::StandardButton btn = QMessageBox::question(this, QString(c->toUnicode("������ �� ���������")), 
																		QString(c->toUnicode("��������� ��������� ����� �������?")), 
																		QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		switch(btn)
		{
			case QMessageBox::StandardButton(QMessageBox::Yes):
				emit saveChanges();
				return this->editState;

			case QMessageBox::StandardButton(QMessageBox::No):
				emit cancelChanges();
				return this->editState;

			case QMessageBox::StandardButton(QMessageBox::Cancel):
			default:
				return true;
		}
	}

	return false;
}

/*!
*\
*/
void SalaryCount::showPage(QAction* actionEmited)
{
	if(!isEditable())
	{
		QString namePage = actionEmited->whatsThis();

		emit showPaget(namePage);

		this->currentAction->setEnabled(true);
		this->currentAction = actionEmited;
		this->currentAction->setEnabled(false);

		showStackedItem(namePage);
	}
}

/*!
*\
*/
void SalaryCount::showCompanyDialog(QAction* actionEmited)
{
	if(actionEmited == ui.ExitAction)
	{
		return;
	}

    QMessageBox::information(NULL,QString::fromWCharArray(L"��� ������ �����"),QString::fromWCharArray(L"������� ������������ ����������� ����������.\n� ��������� ����� �� ������ �������� � ����� ������������� ������������."));
}

/*!
*\
*/
void SalaryCount::showStackedItem(QString namePage)
{
	QWidget* searchPage = ui.stackedWidget->findChild<QWidget*>(namePage);

	if(searchPage && namePage.compare( searchPage->accessibleName() ))
	{
		ui.stackedWidget->setCurrentWidget(searchPage);
	}
	else
	{
		QTextCodec* c = QTextCodec::codecForLocale();
		QMessageBox::critical(this,c->toUnicode(""), c->toUnicode("�������� �� ����������"));
	}
}

/*!
*\
*/
void SalaryCount::rememberState(bool state)
{
	this->editState = state;
}