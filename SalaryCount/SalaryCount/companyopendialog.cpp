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