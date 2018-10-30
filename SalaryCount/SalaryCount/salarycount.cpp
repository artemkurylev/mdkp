#include "salarycount.h"

#include <QtTest/QtTest>
#include "dbmanager.h"
#include"qsqldatabase.h"

#include "unittest/DirectiveGeneratorTest.h"


SalaryCount::SalaryCount(QWidget *parent)
    : QMainWindow(parent)
{
    
    ui.setupUi(this);
    DbManager manager("localhost","salarycount",3306,"root","root");
    if(manager.checkConnection())
    {
        //Создание таблиц
        bool b = Employee::createDbTable();
        if(b)
        {

        }
    }
    else
    {

    }
	QTest::qExec( new DirectiveGeneratorTest(0) , NULL , NULL);
	//заполнение шаблона редактирования графика
	for(int i=0; i<7;++i)
	{

		QComboBox* combo = new QComboBox();

		QTextCodec* codec = QTextCodec::codecForLocale();
		combo->insertItem(0, codec->toUnicode("Рабочий"));

		combo->insertItem(1, codec->toUnicode("Выходной"));

		ui.DutyChartMarksEdit->setCellWidget(i,0,combo);
	}
	
	ui.saveDutyChartBtn->setEnabled(true);
	ui.cancelDutyChartBtn->setEnabled(true);

	connect(ui.addDutyChart,SIGNAL(pressed()), this,SLOT(addDutyChart()));
	connect(ui.payFormChoice,SIGNAL(currentIndexChanged(int)), this,SLOT(changePayForm(int)));
}

SalaryCount::~SalaryCount()
{

}

void SalaryCount::addDutyChart()
{
}

void SalaryCount::changePayForm(int index)
{

}

void SalaryCount::saveNewDutyChart()
{
	
}

void SalaryCount::cancelNewDutyChart()
{

}
