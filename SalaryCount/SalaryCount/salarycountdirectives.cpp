#include "salarycountdirectives.h"

salarycountDirectives::salarycountDirectives(Ui_SalaryCount* ui, QString name)
{
    this->setObjectName(name);
	this->ui = ui;//не самый приятный способ
}

salarycountDirectives::~salarycountDirectives()
{

}
void salarycountDirectives::updateInfo(QString name)
{

}