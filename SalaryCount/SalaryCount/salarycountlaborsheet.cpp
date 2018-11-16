#include "salarycountlaborsheet.h"

salarycountLaborSheet::salarycountLaborSheet(Ui_SalaryCount *ui, QString name)
{
	viewedPeriod = BillingPeriod.getCurrentPeriod();

	
	this->setObjectName(name);
	this->ui = ui;//не самый приятный способ
    for(int i=0; i<31+6;++i)
	{
        QComboBox* combo = new QComboBox();

		QTextCodec* codec = QTextCodec::codecForLocale();

		combo->insertItem(0, codec->toUnicode("-"));

		combo->setCurrentIndex(0);

        ui->laborSheet->setCellWidget(i/7,i % 7,combo);
	}
    ui->LabourGroupEdit->setEnabled(false);
    ui->employeeLaborSheetTable->setColumnWidth(0,0);
    showAllLabors();
}

salarycountLaborSheet::~salarycountLaborSheet()
{

}

void salarycountDutyChart::updateInfo(QString name)
{
	if(!this->objectName().compare(name) && false /* maybe */ )
	{
		//QMap<int,QString> allEntries = DutyChart::getAll();
		//ui->dutyChartList->clear();

		//if(allEntries.count() > 0)
		//{
		//	QList<int> &keys = allEntries.keys();
		//	QList<QString> &val = allEntries.values();
		//	qSort(keys);

		//	foreach(const int &iter, keys)
		//	{
		//		QString d = allEntries.value( iter );
		//		QListWidgetItem *item = new QListWidgetItem(allEntries.value( iter ), ui->dutyChartList, iter);
		//		ui->dutyChartList->addItem(item);
		//	}

		//	ui->dutyChartList->setCurrentRow(0);
		//}
	}
}

void salarycountLaborSheet::showAllLabors()
{
    QMap <int,int> laborData = LaborSheet::getAll(); // ! все или за месяц ?
    int row = 0;
    for(auto it = laborData.begin(); it!= laborData.end(); ++it)
    {
        ui->employeeLaborSheetTable->insertRow(row);
        Employee employee(it.value());
        employee.fetch();
        ui->employeeLaborSheetTable->setItem(row,1,new QTableWidgetItem(employee.fio()));
        ui->employeeLaborSheetTable->setItem(row,0,new QTableWidgetItem(QString(it.key())));
        ++row;
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
