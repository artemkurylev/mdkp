#include "salarycount.h"

#include <QtTest/QtTest>
#include "unittest/DirectiveGeneratorTest.h"


SalaryCount::SalaryCount(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	QTest::qExec( new DirectiveGeneratorTest(0) , NULL , NULL);
	for(int i=0; i<7;++i){

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
		Mark m();
		int markValue = combo->currentIndex();

		if(ui.payFormChoice->currentIndex()==0)
		{
			if(markValue==0) 
			{
				m.setBase(Mark::Type::ATTENDS);
			}

			if(markValue==1) 
			{
				m.setBase(Mark::Type::HOLIDAY);
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
				m.setBase(Mark::Type::HOLIDAY);
			}
		}
		marks.append(m);
	}
	DutyChart dch(marks);
	dch.set();
}

void SalaryCount::cancelNewDutyChart()
{

}