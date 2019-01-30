#include "salarycountprofile.h"
#include "salarycount.h"

SalaryCountProfile::SalaryCountProfile(Ui_SalaryCount *ui, QString name)
{
    this->setObjectName(name);
	this->ui = ui;

	connect(ui->CompanyStart_Button,SIGNAL(clicked()), this,SLOT(startCompany())); // ������� ��������� (���������) ������
}

SalaryCountProfile::~SalaryCountProfile()
{

}
void SalaryCountProfile::updateInfo(QString name)
{
    int count_employees = Employee::countEntries();
    int closed_periods = BillingPeriod::countEntries() - 1;
    ui->countEmployeesLabel->setText(QString::number(count_employees));
    ui->companyNameLabel->setText(Company::currentCompany->name());
    ui->creationDateLabel->setText(Company::currentCompany->date().toString());
    ui->countClosedPeriodsLabel->setText(QString::number(closed_periods));
    ui->currentPeriodLabel->setText(BillingPeriod::getCurrentPeriod()->startDate().toString());

	bool company_initialized = closed_periods > 0; // BillingPeriod::countEntries() > 1;
	ui->CompanyStart_Button->setVisible( !company_initialized );
}


void SalaryCountProfile::startCompany()
{
	QTextCodec* c = QTextCodec::codecForLocale();
	QMessageBox::StandardButton btn = QMessageBox::question(SalaryCount::globalApp, QString(c->toUnicode("������ ������ �����������")), 
												QString(c->toUnicode("������ ������ �����������?\n����� ����� �� ������� ��������� ����� ����������� ������� ������ �� ���������� ����������� ������.")), 
												QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Cancel);
	switch(btn)
	{
		case QMessageBox::StandardButton(QMessageBox::Yes):
			break; // ����������

		case QMessageBox::StandardButton(QMessageBox::Cancel):
		default:
			return; // �����
	}

	bool ok = BookKeeper::closeBillingPeriod( *BillingPeriod::getCurrentPeriod() );
	if(!ok)
	{
		// ERROR !!!
		ui->CompanyStart_Button->setText("������ ������������� ����������� ...");
	}

	this->updateInfo("");
}
