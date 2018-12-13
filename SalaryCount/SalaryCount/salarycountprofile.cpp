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

}