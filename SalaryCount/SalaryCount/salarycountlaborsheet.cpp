#include "salarycountlaborsheet.h"

salarycountLaborSheet::salarycountLaborSheet(Ui_SalaryCount *ui, QString name){
    this->setObjectName(name);
	this->ui = ui;//�� ����� �������� ������
    for(int i=0; i<31;++i)
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
void salarycountLaborSheet::showAllLabors()
{
    QMap <int,int> laborData = LaborSheet::getAll();
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
        int row = 0;
        for(int i = 0;i <marks.size();++i){
            QComboBox* combo = (QComboBox*)ui->DutyChartMarksEdit->cellWidget(i/7,i%7);
            combo->insertItem(0,"��������");
            combo->insertItem(1,"�������");
            combo->insertItem(2,"������������");
            if(marks[i].altered() == Mark::Type::INVALID)
            {
                switch(marks[i].base())
                {
                    case Mark::Type::HOLIDAY:
                    {
                        combo->setCurrentIndex(0);
                        break;
                    }
                    case Mark::Type::ATTENDS:
                    {
                        combo->setCurrentIndex(1);
                        break;
                    }
                    case Mark::Type::MISS:
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
                    case Mark::Type::HOLIDAY:
                    {
                        combo->setCurrentIndex(0);
                        break;
                    }
                    case Mark::Type::ATTENDS:
                    {
                        combo->setCurrentIndex(1);
                        break;
                    }
                    case Mark::Type::MISS:
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
        int row = 0;
        for(int i = 0;i <marks.size();++i)
        {
            QComboBox* combo = (QComboBox*)ui->DutyChartMarksEdit->cellWidget(i/7,i%7);
            for(int j = 0; j <= 12; ++j)
            {
                combo->insertItem(j,QString(j));
            }
            if(marks[i].alteredCountHours() == Mark::Type::INVALID) 
                combo->setCurrentIndex(marks[i].countHours());
            else
                combo->setCurrentIndex(marks[i].alteredCountHours());
        }
    }
}
