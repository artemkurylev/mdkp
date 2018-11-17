#include "salarycountlaborsheet.h"

salarycountLaborSheet::salarycountLaborSheet(Ui_SalaryCount *ui, QString name)
{
	this->setObjectName(name);
	this->ui = ui;//не самый приятный способ

	BillingPeriod* viewedPeriod = BillingPeriod::getCurrentPeriod();
	connect(ui.PeriodDateEdit,SIGNAL(dateChanged(const QDate&)), this,SLOT(periodDateChanged(const QDate&))); // обновить дату текущего периода

	
    int startDay = viewedPeriod->startDate().dayOfWeek() - 1;
    for(int i=startDay; i<31+startDay;++i)
	{
        QComboBox* combo = new QComboBox();

		QTextCodec* codec = QTextCodec::codecForLocale();

		combo->insertItem(0, codec->toUnicode("-"));

		combo->setCurrentIndex(0);

        ui->laborSheet->setCellWidget(i/7,i % 7,combo);
	}
    ui->LabourGroupEdit->setEnabled(false);
    ui->employeeLaborSheetTable->setColumnWidth(0,0);
}

salarycountLaborSheet::~salarycountLaborSheet()
{
	delete viewedPeriod;
}
void salarycountLaborSheet::switchMode(app_states state)
{
	this->currentState = state;

	bool triggerState = false;
	if(state==app_states::EDIT)
	{
		triggerState = true;
	}

	ui->dutyChartEdit->setEnabled(triggerState);
	ui->dutyChartBox->setEnabled(!triggerState);

	emit changeState(triggerState); // может быть, лучше сделать наоборот - чтобы переключение происходило по этому сигналу ???
}
void salarycountLaborSheet::updateInfo(QString name)
{
    QList<LaborSheet> labor_data = LaborSheet::getByPeriodId(viewedPeriod->id());
    if(!this->objectName().compare(name) && ui->employeeLaborSheetTable->rowCount() != labor_data.size())
	{
        ui->employeeLaborSheetTable->clearContents();
        int row = 0;
        for(int i = 0; i < labor_data.size(); ++i)
        {
            ui->employeeLaborSheetTable->insertRow(row);
            Employee employee(*(labor_data[i].employee()));
            ui->employeeLaborSheetTable->setItem(row,0,new QTableWidgetItem(QString(labor_data[i].id())));
            ui->employeeLaborSheetTable->setItem(row,1,new QTableWidgetItem(employee.fio()));
            ui->employeeLaborSheetTable->item(row,0)->setData(Qt::UserRole,labor_data[i].id());
            ++row;
        }
        ui->employeeLaborSheetTable->setCurrentCell(0,1);
	}
}

void salarycountLaborSheet::showLabor()
{
    int row = ui->employeeLaborSheetTable->currentIndex().row();
    int id = ui->employeeLaborSheetTable->item(row,0)->text().toInt();
    LaborSheet labor_sheet(id);
    labor_sheet.fetch();
    QList<Mark>marks = labor_sheet.marks();
    if(labor_sheet.payForm() == PayForm::PER_MONTH)
    {
        //int row = 0;
        for(int i = 0;i <marks.size();++i){
            QComboBox* combo = (QComboBox*)ui->DutyChartMarksEdit->cellWidget(i/7,i%7);
            combo->insertItem(0,"Выходной");
            combo->insertItem(1,"Рабочий");
            combo->insertItem(2,"Отсутствовал");
            if(marks[i].altered() == Mark::INVALID)
            {
                switch(marks[i].base())
                {
                    case Mark::HOLIDAY:
                    {
                        combo->setCurrentIndex(0);
                        break;
                    }
                    case Mark::ATTENDS:
                    {
                        combo->setCurrentIndex(1);
                        break;
                    }
                    case Mark::MISS:
                    {
                        combo->setCurrentIndex(2);
                        break;
                    }
                }
            }
            else
            {
                switch(marks[i].altered())
                {
                    case Mark::HOLIDAY:
                    {
                        combo->setCurrentIndex(0);
                        break;
                    }
                    case Mark::ATTENDS:
                    {
                        combo->setCurrentIndex(1);
                        break;
                    }
                    case Mark::MISS:
                    {
                        combo->setCurrentIndex(2);
                        break;
                    }
                }
            }
        }
    }
    else
    {
        //int row = 0;
        for(int i = 0;i <marks.size();++i)
        {
            QComboBox* combo = (QComboBox*)ui->DutyChartMarksEdit->cellWidget(i/7,i%7);
            for(int j = 0; j <= 12; ++j)
            {
                combo->insertItem(j,QString(j));
            }
            if(marks[i].alteredCountHours() == Mark::INVALID) 
                combo->setCurrentIndex(marks[i].countHours());
            else
                combo->setCurrentIndex(marks[i].alteredCountHours());
        }
    }
}
void salarycountLaborSheet::periodDateChanged(const QDate& date)
{
}