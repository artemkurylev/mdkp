#include "companycreationdialog.h"


companyCreationDialog::companyCreationDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

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
    if(pass_first != pass_repeat)
    {
        return;
    }
    Company company(name,pass_first);
    if(company.validate())
    {
        if(company.insert())
        {
            companyOpenDialog* open = new  companyOpenDialog();
            this->close();
            open->show();
        }
    }
    else{
        //Обработка ошибок!
    }

}
