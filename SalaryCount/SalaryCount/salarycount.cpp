#include "salarycount.h"

SalaryCount::SalaryCount(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	for(int i=0; i<7;++i){

		QComboBox* combo = new QComboBox();

		QTextCodec* codec = QTextCodec::codecForLocale();
		combo->insertItem(0, codec->toUnicode("Выходной"));

		combo->insertItem(1, codec->toUnicode("Рабочий"));

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

}

void SalaryCount::cancelNewDutyChart()
{

}