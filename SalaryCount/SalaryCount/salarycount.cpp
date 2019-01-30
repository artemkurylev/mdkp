#include "salarycount.h"


#include <QtTest/QtTest>
#include <QShortcut>
#include "dbmanager.h"
#include "dutychart.h"
#include"qsqldatabase.h"

#include "unittest/DirectiveGeneratorTest.h"
#include "SalaryCountGuiTester.h"
<<<<<<< HEAD

// ���������� ��������� �� �������� ���� ����������
/*static*/ SalaryCount* SalaryCount::globalApp = NULL;
=======
>>>>>>> ee6c15c... Привязка запуска тестов по сочетанию клавиш Ctrl+T

// ���������� ��������� �� �������� ���� ����������
/*static*/ SalaryCount* SalaryCount::globalApp = NULL;

SalaryCount::SalaryCount(QString dbName, QWidget *parent)
    : QMainWindow()
{
    ui.setupUi(this);

	SalaryCount::globalApp = this;

<<<<<<< HEAD
	initialDBManager(dbName);

=======
>>>>>>> 98daa92... Запуск тестов по нажатию `Ctrl+T` при помощи класса Tester
	this->editState = false;
	
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
	connect(this,SIGNAL(cancelChanges()),this->employees,SLOT(cancelNewEmployee()));//���������� �������� ������ ������ ��������������
	
    //����������� �� ��������� �������
    this->laborSheet = new salarycountLaborSheet(&this->ui,ui.LaborSheetAction->whatsThis());
	connect(this, SIGNAL(showPaget(QString)),this->laborSheet,SLOT(updateInfo(QString)));//�������� ���������� �� ��������
    //���������� �� ��������� ��������
    this->directives = new salarycountDirectives(&this->ui,ui.HireDirectiveAction->whatsThis());
    connect(this, SIGNAL(showPaget(QString)),this->directives,SLOT(updateInfo(QString)));
    //���������� � ��������
    this->profile = new SalaryCountProfile(&this->ui,ui.ShowProfileAction->whatsThis());
    connect(this, SIGNAL(showPaget(QString)),this->profile,SLOT(updateInfo(QString)));

	ui.saveDutyChartBtn->setEnabled(true);
	ui.cancelDutyChartBtn->setEnabled(true);

	//������������ �������
	ui.stackedWidget->setCurrentIndex(2);//������������� ��������� �� �������� � ������������
	this->currentAction = ui.DutyCharAction;
	this->currentAction->setEnabled(false);

	connect(ui.CompanyMenu,SIGNAL(triggered(QAction*)), this,SLOT(showPage(QAction*)));

	connect(ui.FileMenu,SIGNAL(triggered(QAction*)), this,SLOT(showCompanyDialog(QAction*)));

	connect(ui.ExitAction,SIGNAL(triggered()), this,SLOT(close()));

<<<<<<< HEAD
<<<<<<< HEAD
	//showPage(ui.DutyCharAction);
	showPage(ui.LaborSheetAction);
=======
	showPage(ui.DutyCharAction);
>>>>>>> ee6c15c... Привязка запуска тестов по сочетанию клавиш Ctrl+T
=======
	//showPage(ui.DutyCharAction);
	showPage(ui.EmployeeListAction);
>>>>>>> 98daa92... Запуск тестов по нажатию `Ctrl+T` при помощи класса Tester


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
	// ������ ����� �������������� manager, �.�. � �������� ������ ��
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

<<<<<<< HEAD
<<<<<<< HEAD

void SalaryCount::startTesting()
{
	QMessageBox::StandardButton btn = QMessageBox::information(this, QString::fromWCharArray(L"����� ������������"), QString::fromWCharArray(L"����� ����������� �\n����� ��������������� ������������ GUI!\n\n������� `������`, ����� �� ��������� ����� � ����� �� ������ ������������.")
		, QMessageBox::Yes | QMessageBox::Cancel); 

	switch(btn)
	{
		case QMessageBox::StandardButton(QMessageBox::Yes):
			break; // ����������

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
	QMessageBox::information(this, QString::fromWCharArray(L"����� ������������"), QString::fromWCharArray(L"������������ GUI ���������!\n���������� ����������� ������: %1.").arg(failedTests) ); 
=======
=======

>>>>>>> 98daa92... Запуск тестов по нажатию `Ctrl+T` при помощи класса Tester
void SalaryCount::startTesting()
{
	QMessageBox::StandardButton btn = QMessageBox::information(this, QString::fromWCharArray(L"����� ������������"), QString::fromWCharArray(L"����� ����������� �\n����� ��������������� ������������ GUI!\n\n������� `������`, ����� �� ��������� ����� � ����� �� ������ ������������.")
		, QMessageBox::Yes | QMessageBox::Cancel); 

	switch(btn)
	{
		case QMessageBox::StandardButton(QMessageBox::Yes):
			break; // ����������

		case QMessageBox::StandardButton(QMessageBox::Cancel):
		default:
			return;
	}


	Tester *tester = new Tester;
	connect(this, &SalaryCount::runTestThread, tester, &Tester::runTests);
	connect(tester, &Tester::testingFinished, this, &SalaryCount::finishTesting);

	// no-new-thread mode
	connect(tester, &Tester::testingFinished, tester, &QObject::deleteLater);

<<<<<<< HEAD
	QMessageBox::information(this, QString::fromWCharArray(L"����� ������������"), QString::fromWCharArray(L"������������ GUI ���������!\n���������� ����������� ������: %1.").arg(r) ); 
>>>>>>> ee6c15c... Привязка запуска тестов по сочетанию клавиш Ctrl+T
=======
	emit this->runTestThread( &this->ui );
}

void SalaryCount::finishTesting(int failedTests)
{
	QMessageBox::information(this, QString::fromWCharArray(L"����� ������������"), QString::fromWCharArray(L"������������ GUI ���������!\n���������� ����������� ������: %1.").arg(failedTests) ); 
>>>>>>> 98daa92... Запуск тестов по нажатию `Ctrl+T` при помощи класса Tester

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
		QString::fromWCharArray(L"�����"),
		QString::fromWCharArray(L"�� �������� �� ������� ������� ������.\n��������� ����� �������.\n����� ���������� ���� ��� ������ ������, ��������� ��������� �����.\n����������?"),
		QMessageBox::Yes | QMessageBox::Cancel);

	switch(btn)
	{
		case QMessageBox::StandardButton(QMessageBox::Yes):
			// ������� ���� � ����������
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