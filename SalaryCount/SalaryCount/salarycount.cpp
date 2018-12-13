#include "salarycount.h"


#include <QtTest/QtTest>
#include "dbmanager.h"
#include "dutychart.h"
#include"qsqldatabase.h"

#include "unittest/DirectiveGeneratorTest.h"

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
	
	//// запуск тестировани€
	DirectiveGeneratorTest dir_gen_test(0);
	QTest::qExec( &dir_gen_test , NULL , NULL);

	//соединение со страницей создани€ графиков
	this->dutyChart = new salarycountDutyChart(&this->ui,ui.DutyCharAction->whatsThis());
	connect(this, SIGNAL(showPaget(QString)),this->dutyChart,SLOT(updateInfo(QString)));//обновить информацию на странице
	connect(this->dutyChart,SIGNAL(changeState(bool)),this,SLOT(rememberState(bool)));//на странице может быть два режима: просмотр и изменение записей
	connect(this,SIGNAL(saveChanges()),this->dutyChart,SLOT(saveNewDutyChart()));//приложение посылает сигнал на сохранение страницы
	connect(this,SIGNAL(cancelChanges()),this->dutyChart,SLOT(cancelNewDutyChart()));//приложение посылает сигнал отмены редактировани€

	//соединение со страницей кадрового учета
	this->employees = new salarycountEmployees(&this->ui,ui.EmployeeListAction->whatsThis());
	connect(this, SIGNAL(showPaget(QString)),this->employees,SLOT(updateInfo(QString)));//обновить информацию на странице
	connect(this->employees,SIGNAL(changeState(bool)),this,SLOT(rememberState(bool)));//на странице может быть два режима: просмотр и изменение записей
	connect(this,SIGNAL(saveChanges()),this->employees,SLOT(saveNewEmployee()));//приложение посылает сигнал на сохранение страницы
	connect(this,SIGNAL(cancelChanges()),this->dutyChart,SLOT(cancelNewEmployee()));//приложение посылает сигнал отмены редактировани€
	
    //—оедиенение со страницей табелей
    this->laborSheet = new salarycountLaborSheet(&this->ui,ui.LaborSheetAction->whatsThis());
	connect(this, SIGNAL(showPaget(QString)),this->laborSheet,SLOT(updateInfo(QString)));//обновить информацию на странице
    //—оединение со страницей приказов
    this->directives = new salarycountDirectives(&this->ui,ui.HireDirectiveAction->whatsThis());
    connect(this, SIGNAL(showPaget(QString)),this->directives,SLOT(updateInfo(QString)));
    //—оединение с профилем
    this->profile = new SalaryCountProfile(&this->ui,ui.ShowProfileAction->whatsThis());
    connect(this, SIGNAL(showPaget(QString)),this->profile,SLOT(updateInfo(QString)));
	//TODO

	ui.saveDutyChartBtn->setEnabled(true);
	ui.cancelDutyChartBtn->setEnabled(true);

	//постраничный переход
	ui.stackedWidget->setCurrentIndex(2);//устанавлиаем видимость на странице с сотрудниками
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

void SalaryCount::initialDBManager(QString dbName)
{
	// первый вызов инициализирует manager, м.б. с заданным именем Ѕƒ
    DbManager& manager = DbManager::manager(dbName);
    if(manager.checkConnection())
    {
        //—оздание таблиц
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
		// должно быть вызвано после создани€ DutyChart и LaborSheet (из-за внешних ключей)
        table_created = Mark::createDbTable();
        if(!table_created)
        {

        }
		// позже это должно выполн€тьс€ при создании предпри€ти€
		initalSetupForTableDutyChart();
    }
	else
	{
		//TODO
	}
}

//! название метода не отражает сути выполн€емых действий
bool SalaryCount::isEditable()
{
	if(this->editState)
	{
		QTextCodec* c = QTextCodec::codecForLocale();
		QMessageBox::StandardButton btn = QMessageBox::question(this, QString(c->toUnicode("ƒанные не сохранены")), 
																		QString(c->toUnicode("—охранить изменени€ перед выходом?")), 
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

	QMessageBox::StandardButton btn = QMessageBox::question(this,
		QString::fromWCharArray(L"¬ыход"),
		QString::fromWCharArray(L"¬ы выходите из текущей учЄтной записи.\nѕрограмма будет закрыта.\n„тобы произвести вход под другим именем, запустите программу снова.\nѕродолжить?"),
		QMessageBox::Yes | QMessageBox::Cancel);

	switch(btn)
	{
		case QMessageBox::StandardButton(QMessageBox::Yes):
			// закрыть окно и приложение
			this->close();

		case QMessageBox::StandardButton(QMessageBox::Cancel):
		default:
			;
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
		QMessageBox::critical(this,c->toUnicode(""), c->toUnicode("—траница не существует"));
	}

}

/*!
*\
*/
void SalaryCount::rememberState(bool state)
{
	this->editState = state;
}