#include "companycreationdialog.h"
#include "company.h"


companyCreationDialog::companyCreationDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

	if(Company::currentCompany)
		ui.CompanyNameEdit->setText(Company::currentCompany->name());


    connect(ui.buttonBox->button(ui.buttonBox->Ok),SIGNAL(clicked()),this,SLOT(createCompany()));
}

companyCreationDialog::~companyCreationDialog()
{

}

void companyCreationDialog::createCompany()
{
    QString name = ui.CompanyNameEdit->text();
    QString pass_first = ui.passEdit->text();
    QString pass_repeat = ui.passRepeatEdit->text();
    QDate date = ui.firstDateEdit->date();
    if(pass_first != pass_repeat)
    {
        //Обработка ошибок!
        return;
    }
    Company* company = new Company(name,pass_first, date);
    if(company->validate())
    {
        if(company->insert())
        {
			if(Company::currentCompany)
			{
				delete Company::currentCompany;
				Company::currentCompany = NULL;
			}

			Company::currentCompany = company;
			
			
			//companyOpenDialog* open = new companyOpenDialog(this);
            //this->close();
            //open->show();
			this->accept();
			return;
        }
		else
		{
			QMessageBox::information(this, QString::fromWCharArray(L"Ошибка"), QString::fromWCharArray(L"Не удалось создать новую компанию.\nВозможно, соединитья с по сети сервером.\nИмя компании: %1.").arg(name));
		
		}
    }
    else
	{
        //Обработка ошибок!
		QMessageBox::information(this, QString::fromWCharArray(L"Ошибка"), QString::fromWCharArray(L"Не удалось создать новую компанию.\nИмя компании занято: %1.").arg(name));
    }
	delete company;
}
