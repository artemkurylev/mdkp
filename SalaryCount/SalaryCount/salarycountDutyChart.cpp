#include "salarycountDutyChart.h"

salarycountDutyChart::salarycountDutyChart(Ui_SalaryCount* ui)
{
	this->ui = ui;//не самый приятный способ

	for(int i=0; i<7;++i)
	{
		QComboBox* combo = new QComboBox();

		QTextCodec* codec = QTextCodec::codecForLocale();

		combo->insertItem(0, codec->toUnicode("Выходной"));
		combo->insertItem(1, codec->toUnicode("Рабочий"));

		combo->setCurrentIndex(1);

		ui->DutyChartMarksEdit->setCellWidget(i,0,combo);
	}

	//работа с графиками
	ui->saveDutyChartBtn->setEnabled(true);
	ui->cancelDutyChartBtn->setEnabled(true);

	connect(ui->addDutyChart,SIGNAL(pressed()), SLOT(addDutyChart()));
	connect(ui->editDutyChart,SIGNAL(pressed()), SLOT(editDutyChart()));
	connect(ui->cancelDutyChartBtn,SIGNAL(pressed()), SLOT(cancelNewDutyChart()));
	connect(ui->payFormChoice,SIGNAL(currentIndexChanged(int)), SLOT(changePayForm(int)));
	//connect(ui->ExitAction,SIGNAL(triggered()), SLOT(close()));
}

salarycountDutyChart::~salarycountDutyChart()
{
	this->ui = NULL;
}

/*!
*\
*/
void salarycountDutyChart::addDutyChart()
{
	clearFields();//clear fields

	editDutyChart();
}

void salarycountDutyChart::editDutyChart()
{
	this->currentState = app_states::ADD;
	emit changeState(true);

	ui->dutyChartEdit->setEnabled(true);

	ui->dutyChartBox->setEnabled(false);
	ui->dutyChartList->setCurrentRow(-1);
}

/*!
*\
*/
void salarycountDutyChart::cancelNewDutyChart()
{
	this->currentState = app_states::USUAL;
	emit changeState(false);
	clearFields();//clear fields

	ui->dutyChartEdit->setEnabled(false);
	ui->dutyChartBox->setEnabled(true);
}

void salarycountDutyChart::changePayForm(int index)
{
	if(index)
	{
		ui->workTimeEdit->setEnabled(true);
	}
	else
	{
		ui->workTimeEdit->setEnabled(false);
	}
}

void salarycountDutyChart::saveNewDutyChart()
{
	/*QList<Mark> marks;

	for(int i=0;i<7;++i)
	{
		QComboBox* combo = (QComboBox*)ui->DutyChartMarksEdit->cellWidget(i,0);
		
		int mark_value = combo->currentIndex();
		int choice_value = ui->payFormChoice->currentIndex();


		Mark m(mark_value);
		DutyChart dch(marks);
		dch.set();
	}*/
	//собрать данные
	//проверить данные
	//что-то сделать: выдать сообщение об ошибке или сохранить данные
}

DutyChart* salarycountDutyChart::shapeDataObject()
{
	return new DutyChart();
}

void salarycountDutyChart::validateData() const
{

}

void salarycountDutyChart::clearFields()
{
	this->ui->nameDutyChart->clear();
	this->ui->startDate->setDateTime(QDateTime(QDate::currentDate()));
	this->ui->workTimeEdit->setTime(QTime(0,0));

	for(int i=this->ui->DutyChartMarksEdit->rowCount()-1; i>=0; --i)
	{
		QComboBox* combo = (QComboBox*)ui->DutyChartMarksEdit->cellWidget(i,0);
		
		if(combo->count()>=2)
		{
			combo->setCurrentIndex(1);
		}
	}

	if(this->ui->payFormChoice->count()>=1)
	{
		this->ui->payFormChoice->setCurrentIndex(0);
	}
}