#include "salarycountlaborsheet.h"

salarycountLaborSheet::salarycountLaborSheet(Ui_SalaryCount *ui, QString name)
{
	BillingPeriod* viewedPeriod = BillingPeriod::getCurrentPeriod();

	
	this->setObjectName(name);
	this->ui = ui;//не самый приятный способ
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


    //Connections
    connect(ui->employeeLaborSheetTable,SIGNAL(currentCellChanged(int,int,int,int)),this, SLOT(showSelectedItem(int)));
}

salarycountLaborSheet::~salarycountLaborSheet()
{

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

	emit changeState(triggerState);
}
void salarycountLaborSheet::updateInfo(QString name)
{
    QList<LaborSheet> labor_data = LaborSheet::getByPeriodId(BillingPeriod::getCurrentPeriod()->id());
    ui->BillingPeriod_dateEdit->setDate(BillingPeriod::getCurrentPeriod()->startDate());
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

void salarycountLaborSheet::showSelectedItem(int row)
{
    QTextCodec* codec = QTextCodec::codecForLocale();
    if(row >= 0)
    {
        int id = ui->employeeLaborSheetTable->item(row,0)->data(Qt::UserRole).toInt();
        LaborSheet labor_sheet(id,0,0,QList<Mark>());
        labor_sheet.fetch();
        QList<Mark>marks = labor_sheet.marks();
        int start = BillingPeriod::getCurrentPeriod()->startDate().dayOfWeek() - 1;
        if(labor_sheet.payForm() == PayForm::PER_MONTH)
        {
            //int row = 0;
        
            for(int i = start;i < marks.size() + start;++i){
                QComboBox* combo = (QComboBox*)ui->laborSheet->cellWidget(i/7,i%7);
                combo->insertItem(0,codec->toUnicode("Выходной"));
                combo->insertItem(1,codec->toUnicode("Рабочий"));
                combo->insertItem(2,codec->toUnicode("Отсутствовал"));
                if(marks[i - start].altered() == Mark::INVALID)
                {
                    switch(marks[i - start].base())
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
                    switch(marks[i - start].altered())
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
            for(int i = start;i <marks.size() + start;++i)
            {
                QComboBox* combo = (QComboBox*)ui->DutyChartMarksEdit->cellWidget(i/7,i%7);
                for(int j = 0; j <= 12; ++j)
                {
                    combo->insertItem(j,QString(j));
                }
                if(marks[i - start].alteredCountHours() == Mark::INVALID) 
                    combo->setCurrentIndex(marks[i].countHours());
                else
                    combo->setCurrentIndex(marks[i].alteredCountHours());
            }
        }
    }
}
void salarycountLaborSheet::periodDateChanged(QDate date)
{
}