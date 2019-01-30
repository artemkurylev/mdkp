#include "salarycount.h"


#include <QtTest/QtTest>
#include "dbmanager.h"
#include"qsqldatabase.h"

#include "unittest/DirectiveGeneratorTest.h"
    : QMainWindow(parent)
{
    ui.setupUi(this);

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
	connect(this, SIGNAL(showPage(QString)),this->dutyChart,SLOT(updateInfo(QString)));//�������� ���������� �� ��������
	connect(this->dutyChart,SIGNAL(changeState(bool)),this,SLOT(rememberState(bool)));//�� �������� ����� ���� ��� ������: �������� � ��������� �������
	connect(this,SIGNAL(saveChanges()),this->dutyChart,SLOT(saveNewDutyChart()));//���������� �������� ������ �� ���������� ��������
	connect(this,SIGNAL(cancelChanges()),this->dutyChart,SLOT(cancelNewDutyChart()));//���������� �������� ������ ������ ��������������

	//���������� �� ��������� ��������� �����
	this->employees = new salarycountEmployees(&this->ui,ui.EmployeeListAction->whatsThis());
	//connect(this, SIGNAL(showPage(QString)),this->dutyChart,SLOT(updateInfo(QString)));//�������� ���������� �� ��������
	//connect(this->dutyChart,SIGNAL(changeState(bool)),this,SLOT(rememberState(bool)));//�� �������� ����� ���� ��� ������: �������� � ��������� �������
	//connect(this,SIGNAL(saveChanges()),this->dutyChart,SLOT(saveNewDutyChart()));//���������� �������� ������ �� ���������� ��������
	//connect(this,SIGNAL(cancelChanges()),this->dutyChart,SLOT(cancelNewDutyChart()));//���������� �������� ������ ������ ��������������
	
    //����������� �� ��������� �������
    this->laborSheet = new salarycountLaborSheet(&this->ui,ui.LaborSheetAction->whatsThis());
	connect(this, SIGNAL(showPage(QString)),this->laborSheet,SLOT(updateInfo(QString)));//�������� ���������� �� ��������
    //���������� �� ��������� ��������
    this->directives = new salarycountDirectives(&this->ui,ui.HireDirectiveAction->whatsThis());
    connect(this, SIGNAL(showPage(QString)),this->directives,SLOT(updateInfo(QString)));
	//TODO

	ui.saveDutyChartBtn->setEnabled(true);
	ui.cancelDutyChartBtn->setEnabled(true);

	//������������ �������
	ui.stackedWidget->setCurrentIndex(0);//������������ ��������� �� �������� � ������������
	this->currentAction = ui.EmployeeListAction;
	this->currentAction->setEnabled(false);

	connect(ui.CompanyMenu,SIGNAL(triggered(QAction*)), this,SLOT(showPage(QAction*)));

	connect(ui.ExitAction,SIGNAL(triggered()), this,SLOT(close()));
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
    }
    else
    {

    }

	//return??
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

		emit showPage(namePage);

		this->currentAction->setEnabled(true);
		this->currentAction = actionEmited;
		this->currentAction->setEnabled(false);

		showStackedItem(namePage);
	}
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