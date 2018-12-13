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

	Company* company = new Company(name,pass);
    if(company->auth()){
        DbManager::companyManager().close();

		if(Company::currentCompany)
		{
			delete Company::currentCompany;
			Company::currentCompany = NULL;
		}
		Company::currentCompany = company;

		SalaryCount* sc = new SalaryCount(name);
        this->close();
        sc->show();

		//this->done(5);
    }
    else
	{
        //Вывести сообщение о неудаче!
		QMessageBox::information(this, QString::fromWCharArray(L"Ошибка"), QString::fromWCharArray(L"Авторизация не пройдена..."));
	}
}
void companyOpenDialog::createCompany()
{
    companyCreationDialog* creator = new companyCreationDialog(this);
    this->hide();
	// ждать завершения работы с диалогом и вернуться сюда
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
    ui.CompanyCombo->clear();
    ui.CompanyCombo_2->clear();
    QMap<int,QString> companies = Company::getAll();

	int curr_index = -1 , i = 0;
    for(auto it = companies.begin(); it != companies.end(); ++it)
    {
        ui.CompanyCombo->addItem(it.value(),it.key());
        ui.CompanyCombo_2->addItem(it.value(),it.key());
		
		if(Company::currentCompany && Company::currentCompany->id() == it.key())
			curr_index = i;

		++i;
    }

	if(curr_index >= 0)
	{
		// set index of current company
		 ui.CompanyCombo->setCurrentIndex(curr_index);
		 ui.CompanyCombo_2->setCurrentIndex(curr_index);
	}
}
