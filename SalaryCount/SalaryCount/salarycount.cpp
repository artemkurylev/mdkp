#include "salarycount.h"


#include <QtTest/QtTest>
#include <QShortcut>
#include "dbmanager.h"
#include "dutychart.h"
#include"qsqldatabase.h"

#include "unittest/DirectiveGeneratorTest.h"
#include "SalaryCountGuiTester.h"

// глобальный указатель на основное окно приложения
/*static*/ SalaryCount* SalaryCount::globalApp = NULL;

// глобальный указатель на основное окно приложения
/*static*/ SalaryCount* SalaryCount::globalApp = NULL;

SalaryCount::SalaryCount(QString dbName, QWidget *parent)
    : QMainWindow()
{
    ui.setupUi(this);

	SalaryCount::globalApp = this;

	initialDBManager(dbName);

	this->editState = false;
	
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
	connect(this,SIGNAL(cancelChanges()),this->employees,SLOT(cancelNewEmployee()));//приложение посылает сигнал отмены редактирования
	
    //Соедиенение со страницей табелей
    this->laborSheet = new salarycountLaborSheet(&this->ui,ui.LaborSheetAction->whatsThis());
	connect(this, SIGNAL(showPaget(QString)),this->laborSheet,SLOT(updateInfo(QString)));//обновить информацию на странице
    //Соединение со страницей приказов
    this->directives = new salarycountDirectives(&this->ui,ui.HireDirectiveAction->whatsThis());
    connect(this, SIGNAL(showPaget(QString)),this->directives,SLOT(updateInfo(QString)));
    //Соединение с профилем
    this->profile = new SalaryCountProfile(&this->ui,ui.ShowProfileAction->whatsThis());
    connect(this, SIGNAL(showPaget(QString)),this->profile,SLOT(updateInfo(QString)));

	ui.saveDutyChartBtn->setEnabled(true);
	ui.cancelDutyChartBtn->setEnabled(true);

	//постраничный переход
	ui.stackedWidget->setCurrentIndex(2);//устанавливаем видимость на странице с сотрудниками
	this->currentAction = ui.DutyCharAction;
	this->currentAction->setEnabled(false);

	connect(ui.CompanyMenu,SIGNAL(triggered(QAction*)), this,SLOT(showPage(QAction*)));

	connect(ui.FileMenu,SIGNAL(triggered(QAction*)), this,SLOT(showCompanyDialog(QAction*)));

	connect(ui.ExitAction,SIGNAL(triggered()), this,SLOT(close()));

	//showPage(ui.DutyCharAction);
	showPage(ui.LaborSheetAction);


	QShortcut *test_shortcut = new QShortcut(QKeySequence(QString("Ctrl+T")), this);
	test_shortcut->setAutoRepeat(false);
	connect(test_shortcut,SIGNAL(activated()), this,SLOT(startTesting()));

}
SalaryCount::~SalaryCount()
{
	delete this->dutyChart;
}

void SalaryCount::initialDBManager(QString dbName)
{
	// первый вызов инициализирует manager, м.б. с заданным именем БД
    DbManager& manager = DbManager::manager(dbName);
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


void SalaryCount::startTesting()
{
	QMessageBox::StandardButton btn = QMessageBox::information(this, QString::fromWCharArray(L"Режим тестирования"), QString::fromWCharArray(L"Бобро поржаловать в\nрежим автоматического тестирования GUI!\n\nНажмите `Отмена`, чтобы не запускать тесты и выйти из режима тестирования.")
		, QMessageBox::Yes | QMessageBox::Cancel); 

	switch(btn)
	{
		case QMessageBox::StandardButton(QMessageBox::Yes):
			break; // продолжить

		case QMessageBox::StandardButton(QMessageBox::Cancel):
		default:
			return;
	}


	Tester *tester = new Tester;
	connect(this, &SalaryCount::runTestThread, tester, &Tester::runTests);
	connect(tester, &Tester::testingFinished, this, &SalaryCount::finishTesting);

	// no-new-thread mode
	connect(tester, &Tester::testingFinished, tester, &QObject::deleteLater);

	emit this->runTestThread( &this->ui );
}

void SalaryCount::finishTesting(int failedTests)
{
	QMessageBox::information(this, QString::fromWCharArray(L"Режим тестирования"), QString::fromWCharArray(L"Тестирование GUI завершено!\nКоличество проваленных тестов: %1.").arg(failedTests) ); 

}

/*!
*\
*/
void SalaryCount::showPage(QAction* actionEmited)
{
	if(!isEditable())
	{
		QString namePage = actionEmited->whatsThis();

		this->currentAction->setEnabled(true);
		this->currentAction = actionEmited;
		this->currentAction->setEnabled(false);

		showStackedItem(namePage);

		emit showPaget(namePage);
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
		QString::fromWCharArray(L"Выход"),
		QString::fromWCharArray(L"Вы выходите из текущей учётной записи.\nПрограмма будет закрыта.\nЧтобы произвести вход под другим именем, запустите программу снова.\nПродолжить?"),
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
void SalaryCount::showCompanyDialog(QAction* actionEmited)
{
	if(actionEmited == ui.ExitAction)
	{
		return;
	}

    QMessageBox::information(NULL,QString::fromWCharArray(L"Это первый релиз"),QString::fromWCharArray(L"Функции переключения предприятий недоступны.\nВ настоящее время Вы можете работать с одним фиксированным предприятием."));
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