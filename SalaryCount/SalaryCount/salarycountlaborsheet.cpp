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
    
}

salarycountLaborSheet::~salarycountLaborSheet()
{

}
