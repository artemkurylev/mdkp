#include "salarycountprofile.h"

SalaryCountProfile::SalaryCountProfile(Ui_SalaryCount *ui, QString name)
{
    this->setObjectName(name);
	this->ui = ui;//не самый приятный способ
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
}