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
	this->updateCompanyList();

    connect(ui.DirectorButtonBox->button(ui.DirectorButtonBox->Ok),SIGNAL(clicked()),this,SLOT(enterCompany()));
    connect(ui.createCompanyBtn,SIGNAL(clicked()),this,SLOT(createCompany()));
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

		//this->done(5);
    }
    else{
        //¬ывести сообщение о неудаче!
    }
}
void companyOpenDialog::createCompany()
{
    companyCreationDialog* creator = new companyCreationDialog(this);
    this->hide();
	// ждать завершени€ работы с диалогом и вернутьс€ сюда
    int ret = creator->exec();

	delete creator;
	if(ret == QDialog::Accepted)
	{
		//accept();
		this->updateCompanyList();
	}
    this->show();
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

void companyOpenDialog::updateCompanyList()
{
    QMap<int,QString> companies = Company::getAll();
    for(auto it = companies.begin(); it != companies.end(); ++it)
    {
        ui.CompanyCombo_2->addItem(it.value(),it.key());
    }
}
