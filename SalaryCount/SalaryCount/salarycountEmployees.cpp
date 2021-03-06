#include "salarycountEmployees.h"

salarycountEmployees::salarycountEmployees(Ui_SalaryCount *ui, QString name)
	:delegateStates()
{
	this->setObjectName(name);
	this->ui = ui;//�� ����� �������� ������

	ui->eOrderNum->setEnabled(false);

	connect(ui->addEmployeeBtn,SIGNAL(pressed()), SLOT(addEmployee()));
	connect(ui->editEmployeeBtn,SIGNAL(pressed()), SLOT(editEmployee()));
	connect(ui->cancelEmployeeBtn,SIGNAL(pressed()), SLOT(cancelNewEmployee()));
	connect(ui->saveEmployeeBtn,SIGNAL(pressed()),this,SLOT(saveNewEmployee()));

	connect(ui->ePayFormChoice,SIGNAL(currentIndexChanged(int)), SLOT(changePayForm(int)));

	//ui->ePayFormChoice->setCurrentIndex(-1);
	this->currentPayForm = PER_MONTH;

	connect(ui->employeeList,SIGNAL(currentRowChanged(int)), SLOT(showSelectedItem(int)));

	//fillDutyChartComboBox(PER_MONTH);
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
		QString str = validateData();
		if(!str.isEmpty()) throw this->journal->validateError(str.toStdString());

		int id = 0;
		if(this->currentState == EDIT)
		{
			QListWidgetItem *item = ui->employeeList->currentItem();
			if(!item) throw this->journal->nullPtr();

			id = item->type();//��������� ���-������ ��� ����
		}

		QString FIO = ui->eFIO->text();
		QString phone = ui->eNumberPhone->text();
		long long INN = ui->INN->text().toLongLong();
		QString pass = ui->ePassword->text();

		QVariant &var = ui->eDutyChart->currentData();
		if(!var.isValid()) throw this->journal->invalidData();
		int dutyChart = ui->eDutyChart->currentData().toInt();

		int hire_dir = ui->eOrderNum->text().toInt();

		Employee *obj = new Employee(id,FIO,phone,INN,dutyChart,hire_dir,pass);
		return obj;
	}
	catch(log_errors::exception_states e)
	{
		show_last_error();
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

		PayForm pf = (ui->ePayFormChoice->currentIndex()==0 ? PER_MONTH : PER_HOUR);
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

		ui->ePayFormChoice->setCurrentIndex(hd->payForm()==PER_MONTH ? 0 : 1);
		ui->eReceiptDate->setDate(hd->hireDate());
		ui->eOrderNum->setText(QString::number(hd->id()));
		ui->eSalary->setValue(hd->salary());

		fillDutyChartComboBox(hd->payForm());
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
		//���������� ����������� �������� ���� ������ �� ������
		QDate minDate = getMinimumRecipientDate();
		if(!minDate.isValid()) throw this->journal->invalidData();
		ui->eReceiptDate->setMinimumDate(getMinimumRecipientDate());

		//���������� ����� ������� � ������ �� ������
		int hdID = getNewHireDirectiveNumber();
		if(hdID==-1) throw this->journal->invalidData();
		ui->eOrderNum->setText(QString::number(hdID));

		//�������� �� ������������ �������� �����
		ui->eSalary->setValue(ui->eSalary->minimum());

		//�������� ���� ����� ������ �����
		ui->ePayFormChoice->setCurrentIndex(0);

		//��������� ����� ���� ���������
		//if(!fillDutyChartComboBox()) throw this->journal->parseError();
	}
	catch(log_errors::exception_states e)
	{
		if(this->currentState != USUAL)
		{
			switchMode(USUAL);//����� � ��������� ���������
		}
	}
}

int salarycountEmployees::getNewHireDirectiveNumber()
{
	try{

		int hdID;

		if((hdID = HireDirective::lastDirectiveId())==-1) 
			throw this->journal->invalidData("���������� �������� ����� ���������� �������");

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
			if(!countDutyChart) throw this->journal->notFound("�� ������� �������� ������� ������, �������� ��� �� �������");

			QMap<int,QString> &charts = DutyChart::getAllByPayForm(pf);

			if(!charts.count()) throw this->journal->invalidData("�� ������� �������� ������� ������, �������� ��� �� �������");

			ui->eDutyChart->clear();

			QList<int> &keys = charts.keys();
			foreach(const int iter, keys)
			{
				/*switch(charts.value(iter))
				{
					ui->eDutyChart->addItem( charts.value(iter),QVariant(iter));
				}*/
			}

			ui->eDutyChart->setCurrentIndex(0);
			this->currentPayForm = pf;

			ui->addEmployeeBtn->setEnabled(true);
		}

		return this->currentPayForm!=pf;
	}
	catch(log_errors::exception_states e)
	{
		show_last_error();
		this->journal->lastConflictNonResolved();

		if(e == log_errors::INVALID_DATA_EX)
		{
			ui->addEmployeeBtn->setEnabled(false);
		}

		return false;
	}
}

void salarycountEmployees::changeCallPayForm(PayForm pf)
{
<<<<<<< HEAD
	if(pf==PER_MONTH)
=======
	if(pf==PayForm::PER_MONTH)
>>>>>>> 5adcc10... Добавлено изменение названий при смене типа оплаты труда
	{
		ui->eSalary_label->setText(QString::fromWCharArray(L"����� (���)"));
		ui->eSalary->setMinimum(8000);
		ui->eSalary->setSingleStep(1000);
	}
	else
	{
		ui->eSalary_label->setText(QString::fromWCharArray(L"����� � ��� (���)"));
		ui->eSalary->setMinimum(100);
		ui->eSalary->setSingleStep(100);
	}
}

QDate salarycountEmployees::getMinimumRecipientDate()
{
	try
	{
		BillingPeriod *curPer = BillingPeriod::getCurrentPeriod();
		if(!curPer) throw this->journal->nullPtr("������ �������� ������� �� ������������������");

		QDate startDate = curPer->startDate();
        if(curPer->startDate().month() == 12)
        {
            startDate.setDate(startDate.year() + 1,1,1);
        }
        else
        {
            startDate.setDate(startDate.year(),startDate.month() + 1,1);
        }
		
	
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

QString salarycountEmployees::validateData()
{
	QTextCodec* c = QTextCodec::codecForLocale();
	QRegExp FIO(QString::fromWCharArray(L"([a-zA-Z�-��-߸�]+[ ]){2}[a-zA-Z�-��-߸�]+")), INN("\\d{12}"), phone("\\+\\d \\(\\d{3}\\) \\d{3} \\d{2} \\d{2}");

	bool l = FIO.exactMatch(ui->eFIO->text());
	if( !FIO.isValid() || !FIO.exactMatch(ui->eFIO->text()) )
		return QString::fromWCharArray(L"������������ ���:\n%1\n������: ������ ���� ��������").arg(ui->eFIO->text());

	if( !INN.isValid() || !INN.exactMatch(ui->INN->text()) )
		return QString::fromWCharArray(L"������������ ���:\n%1\n������ (������ ���� 12 ����): 123456789012").arg(ui->INN->text());

	if( !phone.isValid() || !phone.exactMatch(ui->eNumberPhone->text()) )
		return QString::fromWCharArray(L"������������ ����� ��������:\n%1\n������: +7 (111) 111 11 11").arg(ui->eNumberPhone->text());

<<<<<<< HEAD
<<<<<<< HEAD
	if(this->currentState == ADD) 
		if( ui->ePassword->text().isEmpty() )
			return QString::fromWCharArray(L"������ �� ����� ���� ������");
=======
	if( ui->ePassword->text().isEmpty() )
		return QString::fromWCharArray(L"������ ����� �������").arg(ui->ePassword->text());
>>>>>>> fa493b5... Добавил поле для ввода пароля
=======
	if(this->currentState == ADD) 
		if( ui->ePassword->text().isEmpty() )
			return QString::fromWCharArray(L"������ �� ����� ���� ������");
>>>>>>> f5bde85... Исправлен баг с проверкой пароля в режиме редактирования, а не создания сотрудника

	return QString();
}

void salarycountEmployees::switchMode(app_states state)
{
	this->currentState = state;//�������� ��������� ����������

	bool isAddState = state==ADD;

	//�������� ��������� � ������ ���� ��� ������� �������� ����
	bool triggerState = false;
	if(state!=USUAL)
	{
		triggerState = true;
	}

	//��������� ��������� ����
	if(state==app_states::ADD)
	{
		ui->eReceiptDate->setEnabled(true);
		ui->workingDataBox->setEnabled(true);
	}
	else
	{
		ui->workingDataBox->setEnabled(false);
		ui->eReceiptDate->setEnabled(false);
	}

	ui->personalDataBox->setEnabled(triggerState);
	ui->workingDataBox->setEnabled(triggerState);
	ui->saveEmployeeBtn->setEnabled(triggerState);
	ui->cancelEmployeeBtn->setEnabled(triggerState);

	ui->employeeBox->setEnabled(!triggerState);

	emit changeState(triggerState);//������� ��������� � ������������ ����
}

void salarycountEmployees::saveNewEntries(Employee* obj)
{
	try
	{
		int id;
		if(this->currentState != ADD) 
			throw this->journal->compareError("�������� ��������� ��� ���������� �� ��������� � ���������� ����������");
		if(!obj) throw this->journal->nullPtr();

		if(!obj->validate()) throw this->journal->validateError("������� �� ����� ��� ��� ����� �������� ������� ��� ����");
		if( (id=obj->insert())==-1) throw this->journal->insertError();

		HireDirective* hd = shapeHireDirective(id);
		if(!hd) throw this->journal->nullPtr();
		if(!hd->validate()) throw this->journal->validateError();
		if(hd->insert()==-1) throw this->journal->insertError();

		//�������� �������� � ����� ������
		QListWidgetItem *item = new QListWidgetItem(obj->fio()+"\t\t\t\t"+QString::number(obj->inn()), ui->employeeList, id);
		ui->employeeList->addItem(item);

		ui->employeeList->setCurrentRow(ui->employeeList->count()-1);
		switchMode(USUAL);

		delete hd;
	}
	catch(log_errors::exception_states e)
	{
		show_last_error();
		this->journal->lastConflictNonResolved();

		//if(e!=log_errors::VALIDATE_EX) switchMode(USUAL);
	}
}

void salarycountEmployees::saveEditableEntries(Employee* obj)
{
	try
	{
		//
		if(this->currentState != EDIT) 
			throw this->journal->compareError("�������� ��������� ��� ���������� �� ��������� � ���������� ����������");
		if(!obj) throw this->journal->nullPtr("������ ��� ���������� �� ����������");
		if(!obj->validate()) throw this->journal->validateError("��������� ������ �� �������");
		if(!obj->update()) throw this->journal->updateError("������ �� ����� � ��");

		HireDirective* hd = shapeHireDirective(obj->id());
		if(!hd) throw this->journal->nullPtr();
		if(!hd->validate()) throw this->journal->validateError();
		if(!hd->update()) throw this->journal->updateError();

		//

		QListWidgetItem *item = ui->employeeList->currentItem();
		if(item) item->setText(obj->fio());//+"\t\t"+QString::number(obj->inn()

		switchMode(USUAL);
	}
	catch(log_errors::exception_states e)
	{
		show_last_error();
		this->journal->lastConflictNonResolved();

		//if(e!=log_errors::VALIDATE_EX) switchMode(USUAL);
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

	if(!this->objectName().compare(name))
	{
		fillDutyChartComboBox(PER_MONTH);
	}

	// clear & disable fields on empty list
	cancelNewEmployee();
	switchMode(USUAL);
}

void salarycountEmployees::addEmployee()
{
	switchMode(ADD);
	clearFields();//clear fields

	ui->employeeList->setCurrentRow(-1);
}

void salarycountEmployees::editEmployee()
{
	switchMode(EDIT);
}

void salarycountEmployees::cancelNewEmployee()
{
	if(this->currentState != USUAL)
	{
		switchMode(USUAL);

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
	if(this->currentState != USUAL)
	{
		try
		{
			Employee* obj = shapeDataObject();//������� ������

			if(!obj) throw this->journal->nullPtr( QString::fromWCharArray(L"����� ��������� �� ��� ��������").toStdString() );
	
			switch(this->currentState)
			{
				case ADD:
					saveNewEntries(obj);
				break;

				case EDIT:
					saveEditableEntries(obj);
				break;
			}
			ui->ePassword->clear();

			delete obj;
		}
		catch(log_errors::exception_states e)
		{
			show_last_error();

			if(e!=log_errors::VALIDATE_EX)
			{
				this->journal->lastConflictNonResolved();
				//switchMode(USUAL);
			}
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
<<<<<<< HEAD
		changeCallPayForm(PER_HOUR);
		fillDutyChartComboBox(PER_HOUR);
	}
	else
	{
		changeCallPayForm(PER_MONTH);
		fillDutyChartComboBox(PER_MONTH);
=======
		changeCallPayForm(PayForm::PER_HOUR);
		fillDutyChartComboBox(PayForm::PER_HOUR);
	}
	else
	{
		changeCallPayForm(PayForm::PER_MONTH);
		fillDutyChartComboBox(PayForm::PER_MONTH);
>>>>>>> 5adcc10... Добавлено изменение названий при смене типа оплаты труда
	}
}

void salarycountEmployees::showSelectedItem(int row)
{
	clearFields();

	if(row!=-1 && ui->employeeList->count() > row)
	{
		int ID = ui->employeeList->currentItem()->type();

		Employee curEmp( ID );

		if(!curEmp.fetch()) throw this->journal->fetchError("���� �� �������");
		parseDataObject(&curEmp);

		this->ui->editEmployeeBtn->setEnabled(true);
	}
	else
	{
		this->ui->editEmployeeBtn->setEnabled(false);
    }
}