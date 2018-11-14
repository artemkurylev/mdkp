#include "salarycountlaborsheet.h"

salarycountLaborSheet::salarycountLaborSheet(Ui_SalaryCount *ui, QString name){
    this->setObjectName(name);
	this->ui = ui;//не самый приятный способ
    for(int i=0; i<31;++i)
	{
        QComboBox* combo = new QComboBox();

		QTextCodec* codec = QTextCodec::codecForLocale();

		combo->insertItem(0, codec->toUnicode("-"));

		combo->setCurrentIndex(0);

        ui->laborSheet->setCellWidget(i/7,i % 7,combo);
	}
    ui->LabourGroupEdit->setEnabled(false);

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

        ui->employeeLaborSheetTable->setItem(row,0,new QTableWidgetItem(employee.fio()));
        ++row;
    }
}