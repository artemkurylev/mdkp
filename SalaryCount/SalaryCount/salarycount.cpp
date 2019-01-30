#include "salarycount.h"


#include <QtTest/QtTest>
#include "dbmanager.h"
#include"qsqldatabase.h"

#include "unittest/DirectiveGeneratorTest.h"


    : QMainWindow(parent)
{
    ui.setupUi(this);

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
	
	// ������ ������������
	QTest::qExec( new DirectiveGeneratorTest(0) , NULL , NULL);

	//���������� ������� �������������� �������
	for(int i=0; i<7;++i)
	{
		QComboBox* combo = new QComboBox();

		QTextCodec* codec = QTextCodec::codecForLocale();

		combo->insertItem(0, codec->toUnicode("��������"));
		combo->insertItem(1, codec->toUnicode("�������"));

		combo->setCurrentIndex(1);

		}
	}
	QTest::qExec( new DirectiveGeneratorTest(0) , NULL , NULL);
		ui.DutyChartMarksEdit->setCellWidget(i,0,combo);
	}
	
	ui.saveDutyChartBtn->setEnabled(true);
	ui.cancelDutyChartBtn->setEnabled(true);

	connect(ui.addDutyChart,SIGNAL(pressed()), this,SLOT(addDutyChart()));
	connect(ui.payFormChoice,SIGNAL(currentIndexChanged(int)), this,SLOT(changePayForm(int)));
	connect(ui.ExitAction,SIGNAL(triggered()), this,SLOT(close()));

	//������������ �������
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
		Mark m(0);
		int markValue = combo->currentIndex();

		if(ui.payFormChoice->currentIndex()==0)
		{
			if(markValue==0) 
			{
				m.setBase(Mark.Type.ATTENDS);
			}

			if(markValue==1) 
			{
				m.setBase(Mark::Type.HOLIDAY);
			}
		}
		else
		{
			
			if(markValue==0) 
			{
				m.setBase(ui.workTimeEdit->time().hour());
			}

			if(markValue==1) 
			{
				m.setBase(Mark::Type.HOLIDAY);
			}
		}
		marks.append(m);
	}
	DutyChart dch(marks);
	dch.set();
		
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

/*!������� �� �������� ����� �����������
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

/*!������� �� �������� ������� ����� �����
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

/*!������� �� �������� ��������
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

/*!������� �� �������� ��������
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

/*!������� �� �������� ����� �����������
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

/*!������� �� �������� ������� ����� �����
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

/*!������� �� �������� ��������
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

/*!������� �� �������� ��������
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
		QMessageBox::critical(this,c->toUnicode(""), c->toUnicode("�������� �� ����������"));
	}

}
