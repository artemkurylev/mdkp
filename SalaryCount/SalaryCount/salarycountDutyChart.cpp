#include "salarycountDutyChart.h"

salarycountDutyChart::salarycountDutyChart(Ui_SalaryCount* ui, QString name)
{
	this->setObjectName(name);
	this->ui = ui;//�� ����� �������� ������

	this->ui->editDutyChart->setEnabled(false);
	this->ui->deleteDutyChart->setEnabled(false);

	for(int i=0; i<7;++i)
	{
		QComboBox* combo = new QComboBox();

		QTextCodec* codec = QTextCodec::codecForLocale();

		combo->insertItem(0, codec->toUnicode("��������"));
		combo->insertItem(1, codec->toUnicode("�������"));

		combo->setCurrentIndex(1);

		ui->DutyChartMarksEdit->setCellWidget(i,0,combo);
	}

	//������ � ���������
	ui->saveDutyChartBtn->setEnabled(true);
	ui->cancelDutyChartBtn->setEnabled(true);

	connect(ui->addDutyChart,SIGNAL(pressed()), SLOT(addDutyChart()));
	connect(ui->editDutyChart,SIGNAL(pressed()), SLOT(editDutyChart()));
	connect(ui->cancelDutyChartBtn,SIGNAL(pressed()), SLOT(cancelNewDutyChart()));
	connect(ui->saveDutyChartBtn,SIGNAL(pressed()),this,SLOT(saveNewDutyChart()));
	connect(ui->deleteDutyChart,SIGNAL(pressed()), SLOT(deleteDutyChart(ui->dutyChartList->currentRow())));

	connect(ui->payFormChoice,SIGNAL(currentIndexChanged(int)), SLOT(changePayForm(int)));
	connect(ui->saveDutyChartBtn,SIGNAL(currentRowChanged(int)), SLOT(showSelectedItem(int)));
}

salarycountDutyChart::~salarycountDutyChart()
{
	this->ui = NULL;
}

void salarycountDutyChart::switchMode(app_states state)
{
	this->currentState = state;

	bool triggerState = false;
	if(state==app_states::ADD || state==app_states::EDIT)
	{
		triggerState = true;
	}

	ui->dutyChartEdit->setEnabled(triggerState);
	ui->dutyChartBox->setEnabled(!triggerState);

	emit changeState(triggerState);
}

/*!
*\
*/
void salarycountDutyChart::addDutyChart()
{
	switchMode(app_states::ADD);

	clearFields();//clear fields

	ui->dutyChartList->setCurrentRow(-1);
}

void salarycountDutyChart::editDutyChart()
{
	switchMode(app_states::EDIT);
}

/*!
*\
*/
void salarycountDutyChart::cancelNewDutyChart()
{
	switchMode(app_states::USUAL);

	if(ui->dutyChartList->count())
	{ 
		ui->dutyChartList->setCurrentRow(0);
	}
	else
	{
		clearFields();//clear fields
	}
}

void salarycountDutyChart::deleteDutyChart(int row)
{
	if(row!=-1)
	{
		int ID = ui->dutyChartList->item(row)->type();

		DutyChart* curChart = new DutyChart( ID );

		if(/*curChart->*/0)
		{
			//���� ������� �� ��
			ui->dutyChartList->setCurrentRow(row-1);
			ui->dutyChartList->removeItemWidget(ui->dutyChartList->item(row));
		}
	}
}

void salarycountDutyChart::saveNewDutyChart()
{
	DutyChart* obj = shapeDataObject();//������� ������

	if(obj->validate())
	{//��������� ������
		if(this->currentState == app_states::ADD)
		{
			saveNewEntries(obj);
			return;
		}

		if(this->currentState == app_states::EDIT)
		{
			saveEditableEntries(obj);
			return;
		}
	}
	else
	{
		//���-�� �������: ������ ��������� �� ������
	}
}

void salarycountDutyChart::saveNewEntries(DutyChart* obj)
{
	if(obj->insert())
	{
		//�������� �������� � ����� ������
		QListWidgetItem *item = new QListWidgetItem(obj->name(), ui->dutyChartList, obj->id());
		ui->dutyChartList->addItem(item);

		ui->dutyChartList->setCurrentRow(ui->dutyChartList->count()-1);
		switchMode(app_states::USUAL);
	}
	else
	{
		//�������� �� ������	
	}
}

void salarycountDutyChart::saveEditableEntries(DutyChart* obj)
{
	if(obj->update())
	{
		switchMode(app_states::USUAL);
	}
	else
	{
		//�������� �� ������	
	}
}

DutyChart* salarycountDutyChart::shapeDataObject()
{
	DutyChart* obj = new DutyChart();//� ����������� �� ��������� �������������� �������� ID

	//������� ���
	//��������� ������� ����
	//��������� ��������� �����
	//� ����������� �� ��������� ����� ��������� ������� �����

	//��������� �������
	/*QList<Mark> m = obj->grid();
	for(int i=this->ui->DutyChartMarksEdit->rowCount()-1; i>=0; --i)
	{
		if(m[i].base() == Mark::Type.HOLIDAY)
		{
			QComboBox* combo = (QComboBox*)ui->DutyChartMarksEdit->cellWidget(i,0);
			combo->setCurrentIndex(1);
		}
	}*/

	return obj;
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

void salarycountDutyChart::updateInfo(QString name)
{
	if(!this->objectName().compare(name) && ui->dutyChartList->count() != DutyChart::countEntries())
	{
		QMap<int,QString> allEntries = DutyChart::getAll();
		ui->dutyChartList->clear();

		if(allEntries.count())
		{
			QList<int> keys = allEntries.keys();
			qSort(keys);

			foreach(const int &iter, keys)
			{
				QListWidgetItem *item = new QListWidgetItem(allEntries.value( iter ), ui->dutyChartList, iter);
				ui->dutyChartList->addItem(item);
			}
		}
	}
}

void salarycountDutyChart::parseDataObject(const DutyChart *obj)
{
	ui->nameDutyChart->setText( obj->name() );
	ui->startDate->setDate( obj->anchorDate() );

	bool isMonth = obj->payForm() == PayForm::PER_MONTH;
	ui->payFormChoice->setCurrentIndex( !isMonth );

	if(!isMonth)
	{
		ui->workTimeEdit->setTime(QTime(0,0));
	}

	QList<Mark> m = obj->grid();
	for(int i=this->ui->DutyChartMarksEdit->rowCount()-1; i>=0; --i)
	{
		if(m[i].base() == Mark::Type::HOLIDAY)
		{
			QComboBox* combo = (QComboBox*)ui->DutyChartMarksEdit->cellWidget(i,0);
			combo->setCurrentIndex(1);
		}
	}
}

void salarycountDutyChart::showSelectedItem( int row )
{
	if(row!=-1)
	{
		int ID = ui->dutyChartList->currentItem()->type();

		DutyChart* curChart = new DutyChart( ID );

		if(curChart->fetch())
		{
			parseDataObject(curChart);
		}
		else
		{
			//TODO 
			//error parse
		}

		this->ui->editDutyChart->setEnabled(true);
		this->ui->deleteDutyChart->setEnabled(true);
	}
	else
	{
		this->ui->editDutyChart->setEnabled(false);
		this->ui->deleteDutyChart->setEnabled(false);
	}
}