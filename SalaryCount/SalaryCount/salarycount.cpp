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

	this->editState = false;
	
	// запуск тестирования
	DirectiveGeneratorTest dir_gen_test(0);
	QTest::qExec( &dir_gen_test , NULL , NULL);

	//соединение со страницей создания графиков
	this->dutyChart = new salarycountDutyChart(&this->ui,ui.DutyCharAction->objectName());
    //Соедиенение со страницей табелей
    this->laborSheet = new salarycountLaborSheet(&this->ui,ui.LaborSheetAction->objectName());
	connect(this, SIGNAL(showPage(QString)),this->dutyChart,SLOT(updateInfo(QString)));//обновить информацию на странице
	connect(this->dutyChart,SIGNAL(changeState(bool)),this,SLOT(rememberState(bool)));//на странице может быть два режима: просмотр и изменение записей
	connect(this,SIGNAL(saveChanges()),this->dutyChart,SLOT(saveNewDutyChart()));//приложение посылает сигнал на сохранение страницы
	connect(this,SIGNAL(cancelChanges()),this->dutyChart,SLOT(cancelNewDutyChart()));//приложение посылает сигнал отмены редактирования
	
	//TODO

	ui.saveDutyChartBtn->setEnabled(true);
	ui.cancelDutyChartBtn->setEnabled(true);

	//постраничный переход
	ui.stackedWidget->setCurrentIndex(0);//устанавлиаем видимость на странице с сотрудниками
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
				return false;

			case QMessageBox::StandardButton(QMessageBox::No):
				emit cancelChanges();
				return false;

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