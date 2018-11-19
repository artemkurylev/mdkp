#include "salarycountEmployees.h"

salarycountEmployees::salarycountEmployees(Ui_SalaryCount *ui, QString name)
	:delegateStates()
{
	this->setObjectName(name);
	this->ui = ui;//не самый приятный способ

	ui->eOrderNum->setEnabled(false);

	connect(ui->addEmployeeBtn,SIGNAL(pressed()), SLOT(addEmployee()));
	connect(ui->editEmployeeBtn,SIGNAL(pressed()), SLOT(editEmployee()));
	connect(ui->cancelEmployeeBtn,SIGNAL(pressed()), SLOT(cancelNewEmployee()));
	connect(ui->saveEmployeeBtn,SIGNAL(pressed()),this,SLOT(saveNewEmployee()));

	connect(ui->ePayFormChoice,SIGNAL(currentIndexChanged(int)), SLOT(changePayForm(int)));
	ui->ePayFormChoice->setCurrentIndex(0);
	this->currentPayForm = PayForm::PER_MONTH;

	connect(ui->employeeList,SIGNAL(currentRowChanged(int)), SLOT(showSelectedItem(int)));

	fillDutyChartComboBox(PayForm::PER_MONTH);
	//connect(ui->INN,SIGNAL(textChanged(QString)), SLOT(innField()));
}

//void salarycountEmployees::innField()
//{
//	ui->INN->setCursorPosition(0);
//}

salarycountEmployees::~salarycountEmployees()
{
	this->ui = NULL;
	delete this->journal;
}

Employee* salarycountEmployees::shapeDataObject()
{
	try
	{
		int id = 0;
		if(this->currentState == app_states::EDIT)
		{
			QListWidgetItem *item = ui->employeeList->currentItem();
			if(!item) throw this->journal->nullPtr();

			id = item->type();//проверить как-нибудь это надо
		}

		QString FIO = ui->eFIO->text();
		QString phone = ui->eNumberPhone->text();
		long long INN = ui->INN->text().toLongLong();

		QVariant &var = ui->eDutyChart->currentData();
		if(!var.isValid()) throw this->journal->invalidData();
		int dutyChart = ui->eDutyChart->currentData().toInt();

		int hire_dir = ui->eOrderNum->text().toInt();

		Employee *obj = new Employee(id,FIO,phone,INN,dutyChart,hire_dir);
		return obj;
	}
	catch(log_errors::exception_states e)
	{
		this->journal->lastConflictNonResolved();
		return NULL;
	}
}

HireDirective* salarycountEmployees::shapeHireDirective(int idEmployee)
{
	try
	{
		if(idEmployee==-1)throw this->journal->nullPtr();

		int id = ui->eOrderNum->text().toInt();
		QString FIO = ui->eFIO->text();
		QDate &hd = ui->eReceiptDate->date();
        PayForm pf = (ui->ePayFormChoice->currentIndex()==0 ? PayForm::PER_MONTH : PayForm::PER_HOUR);
		float sal = ui->eSalary->value();

		HireDirective* obj = new HireDirective(id,hd,FIO,pf,sal,idEmployee);
		return obj;
	}
	catch(log_errors::exception_states e)
	{
		this->journal->lastConflictNonResolved();
		return NULL;
	}
}

void salarycountEmployees::parseDataObject(const Employee* obj)
{
	try
	{
		if(!obj) throw this->journal->nullPtr();

		ui->eFIO->setText(obj->fio());
		ui->eNumberPhone->setText(obj->phoneNumber());
		ui->INN->setText(QString::number(obj->inn()));

		HireDirective *hd = new HireDirective(obj->hireDirectiveID());
		if(!hd->fetch()) throw this->journal->fetchError();

		ui->eReceiptDate->setDate(hd->hireDate());
		ui->eOrderNum->setText(QString::number(hd->id()));
		ui->eSalary->setValue(hd->salary());
		ui->ePayFormChoice->setCurrentIndex(hd->payForm()==PayForm::PER_MONTH ? 0 : 1);

		int row = ui->eDutyChart->findData(QVariant(obj->currentDutyChartID()));
		if(row==-1)throw this->journal->invalidData();

		ui->eDutyChart->setCurrentIndex(row);
	}
	catch(log_errors::exception_states e)
	{
		show_last_error();
		this->journal->lastConflictNonResolved();
	}
}

void salarycountEmployees::clearFields()
{
	ui->eFIO->clear();
	ui->INN->clear();
	ui->eNumberPhone->clear();

	try
	{
		//установить минимальное значение даты приема на работу
		QDate minDate = getMinimumRecipientDate();
		if(!minDate.isValid()) throw this->journal->invalidData();
		ui->eReceiptDate->setMinimumDate(getMinimumRecipientDate());

		//установить номер приказа о приеме на работу
		int hdID = getNewHireDirectiveNumber();
		if(hdID==-1) throw this->journal->invalidData();
		ui->eOrderNum->setText(QString::number(hdID));

		//сбросить до минимального значения оклад
		ui->eSalary->setValue(ui->eSalary->minimum());

		//сбросить поле формы оплаты труда
		ui->ePayFormChoice->setCurrentIndex(0);

		//заполнить комбо ящик графиками
		//if(!fillDutyChartComboBox()) throw this->journal->parseError();
	}
	catch(log_errors::exception_states e)
	{
		if(this->currentState != app_states::USUAL)
		{
			switchMode(app_states::USUAL);//откат к состоянию просмотра
		}
	}
}

int salarycountEmployees::getNewHireDirectiveNumber()
{
	try{

		int hdID;

		if((hdID = HireDirective::lastDirectiveId())==-1) 
			throw this->journal->invalidData("невозможно получить номер последнего приказа");

		return hdID+1;
	}
	catch(log_errors::exception_states e)
	{
		show_last_error();
		this->journal->lastConflictNonResolved();
		return	-1;
	}
}

bool salarycountEmployees::fillDutyChartComboBox(PayForm pf)
{
	try
	{
		if(this->currentPayForm!=pf || !ui->eDutyChart->count())
		{
			long countDutyChart = DutyChart::countEntries();
			if(!countDutyChart) throw this->journal->notFound("Не удалось получить графики работы, возможно они не созданы");

			QMap<int,QString> &charts = DutyChart::getAllByPayForm(pf);

			if(!charts.count()) throw this->journal->invalidData("Не удалось получить графики работы, возможно они не созданы");

			ui->eDutyChart->clear();

			QList<int> &keys = charts.keys();
			foreach(const int iter, keys)
			{
				ui->eDutyChart->addItem( charts.value(iter),QVariant(iter));
			}

			ui->eDutyChart->setCurrentIndex(0);
			this->currentPayForm = pf;
		}

		return this->currentPayForm!=pf;
	}
	catch(log_errors::exception_states e)
	{
		show_last_error();
		this->journal->lastConflictNonResolved();

		return false;
	}
}

QDate salarycountEmployees::getMinimumRecipientDate()
{
	try
	{
		BillingPeriod *curPer = BillingPeriod::getCurrentPeriod();
		if(!curPer) throw this->journal->nullPtr("объект текущего периода не проинициализирован");

		QDate startDate = curPer->startDate();
		startDate.setDate(startDate.year(),(startDate.month()!=12 ? startDate.month()+1 : 1),1);
	
		delete curPer;

		return startDate;
	}
	catch(log_errors::exception_states e)
	{
		show_last_error();
		this->journal->lastConflictNonResolved();

		return QDate();
	}
}

void salarycountEmployees::switchMode(app_states state)
{
	this->currentState = state;//запомним состояние приложения
	bool isAddState = state==app_states::ADD;

	//приведем состояние к булеву типу для посылки главному окну
	bool triggerState = false;
	if(state!=app_states::USUAL)
	{
		triggerState = true;
	}

	//изменение состояния окна
	ui->eReceiptDate->setEnabled(isAddState);
	ui->workingDataBox->setEnabled(isAddState);//triggerState
	ui->personalDataBox->setEnabled(triggerState);
	ui->saveEmployeeBtn->setEnabled(triggerState);
	ui->cancelEmployeeBtn->setEnabled(triggerState);

	ui->employeeBox->setEnabled(!triggerState);

	emit changeState(triggerState);//посылка состояния в родительское окно
}

void salarycountEmployees::saveNewEntries(Employee* obj)
{
	try
	{
		int id;
		if(this->currentState != app_states::ADD) 
			throw this->journal->compareError("Значения состояния для сохранения не совпадает с состоянием приложения");
		if(!obj) throw this->journal->nullPtr();
		if(!obj->validate()) throw this->journal->validateError("Кажется вы ввели ИНН или номер телефона который уже есть");
		if( (id=obj->insert())==-1) throw this->journal->insertError();

		HireDirective* hd = shapeHireDirective(id);
		if(!hd) throw this->journal->nullPtr();
		if(!hd->validate()) throw this->journal->validateError();
		if(hd->insert()==-1) throw this->journal->insertError();

		//добавить значение в конец списка
		QListWidgetItem *item = new QListWidgetItem(obj->fio(), ui->employeeList, id);//+"\t\t"+QString::number(obj->inn()
		ui->employeeList->addItem(item);

		ui->employeeList->setCurrentRow(ui->employeeList->count()-1);
		switchMode(app_states::USUAL);

		delete hd;
	}
	catch(log_errors::exception_states e)
	{
		show_last_error();
		this->journal->lastConflictNonResolved();
		switchMode(app_states::USUAL);
	}
}

void salarycountEmployees::saveEditableEntries(Employee* obj)
{
	try
	{
		//
		if(this->currentState != app_states::EDIT) 
			throw this->journal->compareError("Значения состояния для сохранения не совпадает с состоянием приложения");
		if(!obj) throw this->journal->nullPtr("Объект для сохранения не существует");
		if(!obj->validate()) throw this->journal->validateError("Валидация записи не успешна");
		if(!obj->update()) throw this->journal->updateError("Запись не дошла в бд");

		HireDirective* hd = shapeHireDirective(obj->id());
		if(!hd) throw this->journal->nullPtr();
		if(!hd->validate()) throw this->journal->validateError();
		if(!hd->update()) throw this->journal->updateError();

		//
		QListWidgetItem *item = ui->employeeList->currentItem();
		if(item) item->setText(obj->fio());//+"\t\t"+QString::number(obj->inn()

		switchMode(app_states::USUAL);
	}
	catch(log_errors::exception_states e)
	{
		show_last_error();
		this->journal->lastConflictNonResolved();
		switchMode(app_states::USUAL);
	}
}

void salarycountEmployees::updateInfo(QString name)
{
	if(!this->objectName().compare(name) && ui->employeeList->count() != Employee::countEntries())
	{
		QMap<int,QString> allEntries = Employee::getAll();
		ui->employeeList->clear();

		if(allEntries.count() > 0)
		{
			QList<int> &keys = allEntries.keys();
			QList<QString> &val = allEntries.values();
			qSort(keys);

			foreach(const int &iter, keys)
			{
				QString d = allEntries.value( iter );
				QListWidgetItem *item = new QListWidgetItem(allEntries.value( iter ), ui->employeeList, iter);
				ui->employeeList->addItem(item);
			}

			ui->employeeList->setCurrentRow(0);
		}
	}
}

void salarycountEmployees::addEmployee()
{
	switchMode(app_states::ADD);
	clearFields();//clear fields

	ui->employeeList->setCurrentRow(-1);
}

void salarycountEmployees::editEmployee()
{
	switchMode(app_states::EDIT);
}

void salarycountEmployees::cancelNewEmployee()
{
	if(this->currentState != app_states::USUAL)
	{
		switchMode(app_states::USUAL);

		int row = ui->employeeList->currentRow();
		if(row!=-1)
		{ 
			showSelectedItem(row);
		}
		else
		{
			clearFields();//clear fields
		}
	}
}

void salarycountEmployees::saveNewEmployee()
{
	if(this->currentState != app_states::USUAL)
	{
		try
		{
			Employee* obj = shapeDataObject();//собрать данные

			if(!obj) throw this->journal->nullPtr();
	
			switch(this->currentState)
			{
				case app_states::ADD:
					saveNewEntries(obj);
				break;

				case app_states::EDIT:
					saveEditableEntries(obj);
				break;
			}

			delete obj;
		}
		catch(log_errors::exception_states e)
		{
			show_last_error();
			this->journal->lastConflictNonResolved();
			switchMode(app_states::USUAL);
		}
	}
}

//void salarycountEmployees::deleteEmployee()
//{
//
//}

void salarycountEmployees::changePayForm(int index)
{
	if(index)
	{
		fillDutyChartComboBox(PayForm::PER_HOUR);
	}
	else
	{
		fillDutyChartComboBox(PayForm::PER_MONTH);
	}
}

void salarycountEmployees::showSelectedItem(int row)
{
	clearFields();

	if(row!=-1 && ui->employeeList->count() > row)
	{
		int ID = ui->employeeList->currentItem()->type();

		Employee curEmp( ID );

		if(!curEmp.fetch()) throw this->journal->fetchError("фетч не сфетчил");
		parseDataObject(&curEmp);

		this->ui->editEmployeeBtn->setEnabled(true);
	}
	else
	{
		this->ui->editEmployeeBtn->setEnabled(false);
    }
}