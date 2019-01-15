#include "companyopendialog.h"

companyOpenDialog::companyOpenDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
	this->journal = new log_errors();//������ ������ 

    initialDBManager();
    if(!Company::countEntries())
    {
        initializeCompany();
    }
	this->updateCompanyList();

    connect(ui.DirectorButtonBox->button(ui.DirectorButtonBox->Ok),SIGNAL(clicked()),this,SLOT(enterCompany()));
    connect(ui.createCompanyBtn,SIGNAL(clicked()),this,SLOT(createCompany()));

	connect(ui.EmployeeButtonBox->button(ui.EmployeeButtonBox->Ok),SIGNAL(pressed()),this,SLOT(enterEmployee()));
}

void companyOpenDialog::enterCompany()
{
    QString name = ui.CompanyCombo_2->currentText();
    QString pass = ui.companyPassEdit->text();

	Company* company = new Company(name,pass);
    if(company->auth()){
        company->fetch();
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

		this->destroy();
    }
    else
	{
        //������� ��������� � �������!
		QMessageBox::information(this, QString::fromWCharArray(L"������"), QString::fromWCharArray(L"��� �������� ��� ������ ������������.\n����������� �� ��������."));
	}
}
void companyOpenDialog::createCompany()
{
    companyCreationDialog* creator = new companyCreationDialog(this);
    this->hide();
	// ����� ���������� ������ � �������� � ��������� ����
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

void companyOpenDialog::enterEmployee()
{
	try
	{
		QString name = ui.CompanyCombo->currentText();
		QString number = ui.eNumberPhone->text();
		QString pass = ui.ePass->text();

		Employee* employee = new Employee(number,pass);

		DbManager::companyManager().close();

		EmployeeSC* sc = new EmployeeSC(name,employee);
        this->close();
        sc->show();
	}
	catch(log_errors::exception_states e)
	{
		//TODO
	}
}

void companyOpenDialog::error_msg(const char* short_description, const char* text)
{
	QTextCodec* c = QTextCodec::codecForLocale();
	QMessageBox::critical(NULL,c->toUnicode(short_description), c->toUnicode(text));
}