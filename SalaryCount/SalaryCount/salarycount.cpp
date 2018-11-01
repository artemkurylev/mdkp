#include "salarycount.h"

#include <QtTest/QtTest>
#include "dbmanager.h"
#include"qsqldatabase.h"

#include "unittest/DirectiveGeneratorTest.h"


SalaryCount::SalaryCount(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
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
    }
    else
    {

    }
	
	// запуск тестирования
	QTest::qExec( new DirectiveGeneratorTest(0) , NULL , NULL);

	//заполнение шаблона редактирования графика
	for(int i=0; i<7;++i)
	{

		QComboBox* combo = new QComboBox();

		QTextCodec* codec = QTextCodec::codecForLocale();

		combo->insertItem(0, codec->toUnicode("Выходной"));
		combo->insertItem(1, codec->toUnicode("Рабочий"));

		combo->setCurrentIndex(1);

		ui.DutyChartMarksEdit->setCellWidget(i,0,combo);
	}
	
	ui.saveDutyChartBtn->setEnabled(true);
	ui.cancelDutyChartBtn->setEnabled(true);

	connect(ui.addDutyChart,SIGNAL(pressed()), this,SLOT(addDutyChart()));
	connect(ui.payFormChoice,SIGNAL(currentIndexChanged(int)), this,SLOT(changePayForm(int)));
	connect(ui.ExitAction,SIGNAL(triggered()), this,SLOT(close()));

	//постраничный переход
	this->currentAction = ui.EmployeeListAction;
	this->currentAction->setEnabled(false);

	connect(ui.EmployeeListAction,SIGNAL(triggered()), this,SLOT(showEmployeesPage()));
	connect(ui.LaborSheetAction,SIGNAL(triggered()), this,SLOT(showLaborSheetsPage()));
	connect(ui.DutyCharAction,SIGNAL(triggered()), this,SLOT(showDutyChartsPage()));
	connect(ui.HireDirectiveAction,SIGNAL(triggered()), this,SLOT(showHireDirectivesPage()));
}

SalaryCount::~SalaryCount()
{

}

void SalaryCount::addDutyChart()
{
	ui.dutyChartEdit->setEnabled(true);
}

void SalaryCount::changePayForm(int index)
{
	if(index)
	{
		ui.workTimeEdit->setEnabled(true);
	}
	else
	{
		ui.workTimeEdit->setEnabled(false);
	}
}

void SalaryCount::saveNewDutyChart()
{
	QList<Mark> marks;

	for(int i=0;i<7;++i)
	{
		QComboBox* combo = (QComboBox*)ui.DutyChartMarksEdit->cellWidget(i,0);
		
		int mark_value = combo->currentIndex();
		int choice_value = ui.payFormChoice->currentIndex();


		Mark m(mark_value);
		DutyChart dch(marks);
		dch.set();
	}
}

/*!
*\
*/
void SalaryCount::cancelNewDutyChart()
{

}

/*!Переход на страницу учета сотрудников
*\
*/
void SalaryCount::showEmployeesPage()
{
	int indexPage = 0;
	QString namePage = QString("EmployeesPage");

	this->currentAction->setEnabled(true);
	this->currentAction = ui.EmployeeListAction;
	this->currentAction->setEnabled(false);

	showStacketItem(indexPage, namePage);
}

/*!Переход на страницу табелей учета труда
*\
*/
void SalaryCount::showLaborSheetsPage()
{
	int indexPage = 1;
	QString namePage = QString("LaborSheetsPage");

	this->currentAction->setEnabled(true);
	this->currentAction = ui.LaborSheetAction;
	this->currentAction->setEnabled(false);

	showStacketItem(indexPage, namePage);
}

/*!Переход на страницу графиков
*\
*/
void SalaryCount::showDutyChartsPage()
{
	int indexPage = 2;
	QString namePage = QString("DutyChartsPage");

	this->currentAction->setEnabled(true);
	this->currentAction = ui.DutyCharAction;
	this->currentAction->setEnabled(false);

	showStacketItem(indexPage, namePage);
}

/*!Переход на страницу приказов
*\
*/
void SalaryCount::showHireDirectivesPage()
{
	int indexPage = 3;
	QString namePage = QString("HireDirectivesPage");

	this->currentAction->setEnabled(true);
	this->currentAction = ui.HireDirectiveAction;
	this->currentAction->setEnabled(false);

	showStacketItem(indexPage, namePage);
}

void SalaryCount::showStacketItem(int indexPage, QString namePage)
{
	const QWidget* searchPage = ui.stackedWidget->widget(indexPage);

	if(searchPage && namePage.compare( searchPage->accessibleName() ))
	{
		ui.stackedWidget->setCurrentIndex(indexPage);
	}
	else
	{
		QTextCodec* c = QTextCodec::codecForLocale();
		QMessageBox::critical(this,c->toUnicode(""), c->toUnicode("Страница не существует"));
	}
}