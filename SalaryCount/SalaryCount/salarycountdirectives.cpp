#include "salarycountdirectives.h"

#include <QStandardPaths>

const QString DirectivesDir = QString::fromWCharArray(L"�������");

salarycountDirectives::salarycountDirectives(Ui_SalaryCount* ui, QString name)
{
    this->setObjectName(name);
	this->ui = ui;//�� ����� �������� ������
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

		QString filepath = QStandardPaths::writableLocation( QStandardPaths::DocumentsLocation );
		QDir dir(filepath);
		bool ok = dir.mkdir(DirectivesDir);
		if(ok)
			dir.cd(DirectivesDir);
		filepath = dir.absoluteFilePath( directive->fio() + ".pdf ");

        DirectiveGenerator generator;
        generator.pdf(directive,filepath);

        QMessageBox::information(NULL,QString::fromWCharArray(L"���������!"),QString::fromWCharArray(L"�������� ������ � ������� PDF �� ��� %1.\n������������: %2 / %3\n����:\n%4")
			.arg(directive->fio())
			.arg(QStandardPaths::displayName( QStandardPaths::DocumentsLocation ))
			.arg(DirectivesDir)
			.arg(filepath));
		
		delete directive;
    }
    
}