#include "salarycountdirectives.h"


salarycountDirectives::salarycountDirectives(Ui_SalaryCount* ui, QString name)
{
    this->setObjectName(name);
	this->ui = ui;//не самый приятный способ
    connect(ui->showDirectiveBtn,SIGNAL(pressed()),SLOT(showDirective()));
}

salarycountDirectives::~salarycountDirectives()
{

}
void salarycountDirectives::updateInfo(QString name)
{
    if(!this->objectName().compare(name) && ui->directiveList->count() != HireDirective::countEntries())
	{
        QMap<int,QString> allEntries = HireDirective::getAll();
		ui->dutyChartList->clear();

		if(allEntries.count() > 0)
		{
			QList<int> &keys = allEntries.keys();
			QList<QString> &val = allEntries.values();
			qSort(keys);

			foreach(const int &iter, keys)
			{
				QString d = allEntries.value( iter );
				QListWidgetItem *item = new QListWidgetItem(allEntries.value( iter ), ui->directiveList, iter);
				ui->directiveList->addItem(item);
			}

			ui->directiveList->setCurrentRow(0);
            ui->showDirectiveBtn->setEnabled(true);
		}
	}
}
void salarycountDirectives::showDirective()
{
    int row = ui->directiveList->currentRow();
    if(row!=-1 && ui->directiveList->count() > row)
    {
        int id = ui->directiveList->currentItem()->type();
        HireDirective* directive = new HireDirective(id);
        directive->fetch();
        DirectiveGenerator generator;
        generator.pdf(directive,directive->fio() + ".pdf");
        QMessageBox::information(NULL,QString::fromWCharArray(L"Успешно!"),QString::fromWCharArray(L"Создан pdf приказ ")+ directive->fio() + ".pdf");
    }
    
}