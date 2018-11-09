#include "salarycount.h"


#include <QtTest/QtTest>
#include "dbmanager.h"
#include"qsqldatabase.h"

#include "unittest/DirectiveGeneratorTest.h"


    : QMainWindow(parent)
{
    ui.setupUi(this);

    initialDBManager();
	this->editState = false;
	
	// запуск тестировани€
	QTest::qExec( new DirectiveGeneratorTest(0) , NULL , NULL);


	//
	this->dutyChart = new salarycountDutyChart(&this->ui);
	connect(this->dutyChart,SIGNAL(changeState(bool)),this,SLOT(rememberState(bool)));
	connect(this,SIGNAL(saveChanges()),this->dutyChart,SLOT(saveNewDutyChart()));
	connect(this,SIGNAL(cancelChanges()),this->dutyChart,SLOT(cancelNewDutyChart()));

	//постраничный переход
	ui.stackedWidget->setCurrentIndex(0);//устанавлиаем видимость на странице с сотрудниками
	this->currentAction = ui.EmployeeListAction;
	this->currentAction->setEnabled(false);

	connect(ui.CompanyMenu,SIGNAL(triggered(QAction*)), this,SLOT(showPage(QAction*)));
}

SalaryCount::~SalaryCount()
{

}


void SalaryCount::initialDBManager()
{
	DbManager& manager = DbManager::manager();
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
    }
    else
    {

    }

	//return??
}

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
				return false;

			case QMessageBox::StandardButton(QMessageBox::No):
				emit cancelChanges();
				return true;

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