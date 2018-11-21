#include "salarycount.h"

#include <QtTest/QtTest>
#include "dbmanager.h"
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
	
	//// запуск тестирования
	DirectiveGeneratorTest dir_gen_test(0);
	QTest::qExec( &dir_gen_test , NULL , NULL);

	//соединение со страницей создания графиков
	this->dutyChart = new salarycountDutyChart(&this->ui,ui.DutyCharAction->whatsThis());
	connect(this, SIGNAL(showPaget(QString)),this->dutyChart,SLOT(updateInfo(QString)));//обновить информацию на странице
	connect(this->dutyChart,SIGNAL(changeState(bool)),this,SLOT(rememberState(bool)));//на странице может быть два режима: просмотр и изменение записей
	connect(this,SIGNAL(saveChanges()),this->dutyChart,SLOT(saveNewDutyChart()));//приложение посылает сигнал на сохранение страницы
	connect(this,SIGNAL(cancelChanges()),this->dutyChart,SLOT(cancelNewDutyChart()));//приложение посылает сигнал отмены редактирования

	//соединение со страницей кадрового учета
	this->employees = new salarycountEmployees(&this->ui,ui.EmployeeListAction->whatsThis());
	connect(this, SIGNAL(showPaget(QString)),this->employees,SLOT(updateInfo(QString)));//обновить информацию на странице
	connect(this->employees,SIGNAL(changeState(bool)),this,SLOT(rememberState(bool)));//на странице может быть два режима: просмотр и изменение записей
	connect(this,SIGNAL(saveChanges()),this->employees,SLOT(saveNewEmployee()));//приложение посылает сигнал на сохранение страницы
	connect(this,SIGNAL(cancelChanges()),this->dutyChart,SLOT(cancelNewEmployee()));//приложение посылает сигнал отмены редактирования
	
    //Соедиенение со страницей табелей
    this->laborSheet = new salarycountLaborSheet(&this->ui,ui.LaborSheetAction->whatsThis());
	connect(this, SIGNAL(showPaget(QString)),this->laborSheet,SLOT(updateInfo(QString)));//обновить информацию на странице
    //Соединение со страницей приказов
    this->directives = new salarycountDirectives(&this->ui,ui.HireDirectiveAction->whatsThis());
    connect(this, SIGNAL(showPaget(QString)),this->directives,SLOT(updateInfo(QString)));
	//TODO

	ui.saveDutyChartBtn->setEnabled(true);
	ui.cancelDutyChartBtn->setEnabled(true);

	//постраничный переход
	ui.stackedWidget->setCurrentIndex(2);//устанавлиаем видимость на странице с сотрудниками
	this->currentAction = ui.DutyCharAction;
	this->currentAction->setEnabled(false);

	connect(ui.CompanyMenu,SIGNAL(triggered(QAction*)), this,SLOT(showPage(QAction*)));

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
        table_created = Mark::createDbTable();
        if(!table_created)
        {

        }
    }
	else
	{
		//TODO
	}

	//return??
}

//! название метода не отражает сути выполняемых действий
bool SalaryCount::isEditable()
{
	if(this->editState)
	{
		QTextCodec* c = QTextCodec::codecForLocale();
		QMessageBox::StandardButton btn = QMessageBox::question(this, QString(c->toUnicode("Данные не сохранены")), 
																		QString(c->toUnicode("Сохранить изменения перед выходом?")), 
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
		QMessageBox::critical(this,c->toUnicode(""), c->toUnicode("Страница не существует"));
	}
}

/*!
*\
*/
void SalaryCount::rememberState(bool state)
{
	this->editState = state;
}