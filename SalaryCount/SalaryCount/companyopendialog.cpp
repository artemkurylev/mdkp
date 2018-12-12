#include "companyopendialog.h"

companyOpenDialog::companyOpenDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    initialDBManager();
    if(!Company::countEntries())
    {
        initializeCompany();
    }
    QMap<int,QString> companies = Company::getAll();
    for(auto it = companies.begin(); it != companies.end(); ++it){
        ui.CompanyCombo_2->addItem(it.value(),it.key());
    }
    connect(ui.buttonBox_2->button(ui.buttonBox_2->Ok),SIGNAL(clicked()),this,SLOT(enterCompany()));
}

void companyOpenDialog::enterCompany()
{
    QString name = ui.CompanyCombo_2->currentText();
    QString pass = ui.companyPassEdit->text();
    Company company(name, pass);
    if(company.auth()){
        DbManager::companyManager().close();
        SalaryCount* sc = new SalaryCount(name);
        this->close();
        sc->show();
    }
    else{
        //Вывести сообщение о неудаче!
    }
}
companyOpenDialog::~companyOpenDialog()
{

}
void companyOpenDialog::initialDBManager()
{
    DbManager& manager = DbManager::companyManager();
    if(manager.checkConnection())
    {
        bool table_created = Company::createTable();
        if(!table_created)
        {

        }
    }

}