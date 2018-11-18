#include "salarycountEmployees.h"

salarycountEmployees::salarycountEmployees(Ui_SalaryCount *ui, QString name)
{
	this->setObjectName(name);
	this->ui = ui;//не самый приятный способ

	journal = new log_errors();//журнал ошибок

	connect(ui->addEmployeeBtn,SIGNAL(pressed()), SLOT(addEmployee()));
	/*connect(ui->editDutyChart,SIGNAL(pressed()), SLOT(editDutyChart()));
	connect(ui->cancelDutyChartBtn,SIGNAL(pressed()), SLOT(cancelNewDutyChart()));
	connect(ui->saveDutyChartBtn,SIGNAL(pressed()),this,SLOT(saveNewDutyChart()));
	connect(ui->deleteDutyChart,SIGNAL(pressed()), SLOT(deleteDutyChart()));

	connect(ui->payFormChoice,SIGNAL(currentIndexChanged(int)), SLOT(changePayForm(int)));
	connect(ui->dutyChartList,SIGNAL(currentRowChanged(int)), SLOT(showSelectedItem(int)));*/
}

salarycountEmployees::~salarycountEmployees()
{

}

Employee* salarycountEmployees::shapeDataObject()
{
	return NULL;
}

void salarycountEmployees::parseDataObject(const Employee* obj)
{

}

void salarycountEmployees::clearFields()
{
	ui->eFIO->clear();
	ui->eBDay->clear();
	ui->INN->clear();
	ui->eNumberPhone->clear();

	try
	{
		BillingPeriod *curPer = BillingPeriod::getCurrentPeriod();
		if(!curPer) throw this->journal->nullPtr("объект текущего периода не проинициализирован");

		QDate startDate = curPer->startDate();
		startDate.setDate(startDate.year(),(startDate.month()!=12 ? startDate.month()+1 : 1),1);
		ui->eReceiptDate->setMinimumDate(startDate);


	}
	catch(log_errors::exception_states e)
	{
		QByteArray code = QString::number(this->journal->getLastErrorCode()).toLocal8Bit();
		QByteArray msg = this->journal->getLastError().toLocal8Bit();

		error_msg(code.data(),msg.data());//cообщили об ошибке
		this->journal->lastConflictNonResolved();
	}
}

void salarycountEmployees::switchMode(app_states state)
{
	this->currentState = state;//запомним состояние приложения

	//приведем состояние к булеву типу для посылки главному окну
	bool triggerState = false;
	if(state!=app_states::USUAL)
	{
		triggerState = true;
	}

	//изменение состояния окна
	ui->personalDataBox->setEnabled(triggerState);
	ui->workingDataBox->setEnabled(triggerState);
	ui->saveEmployeeBtn->setEnabled(triggerState);
	ui->cancelEmployeeBtn->setEnabled(triggerState);

	ui->employeeBox->setEnabled(!triggerState);

	emit changeState(triggerState);//посылка состояния в родительское окно
}

void salarycountEmployees::saveNewEntries(Employee* obj)
{

}

void salarycountEmployees::saveEditableEntries(Employee* obj)
{

}

void salarycountEmployees::updateInfo(QString name)
{

}

void salarycountEmployees::addEmployee()
{
	switchMode(app_states::ADD);
	clearFields();//clear fields

	ui->employeeList->setCurrentRow(-1);
}

void salarycountEmployees::editEmployee()
{

}

void salarycountEmployees::cancelNewEmployee()
{

}

void salarycountEmployees::saveNewEmployee()
{

}

void salarycountEmployees::deleteEmployee()
{

}

void salarycountEmployees::changePayForm(int index)
{

}

void salarycountEmployees::showSelectedItem(int row)
{

}