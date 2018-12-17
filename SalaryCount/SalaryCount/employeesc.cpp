#include "employeesc.h"

#include "dbmanager.h"
#include"qsqldatabase.h"

#include "unittest/DirectiveGeneratorTest.h"


EmployeeSC::EmployeeSC(QString &dbName,Employee* employee, QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	this->journal = new log_errors();//журнал ошибок 

	try
	{
		if(dbName.isEmpty() && !employee) throw this->journal->nullPtr("Connection error");

		initialDBManager(dbName);

		if(!employee->auth()) 
				throw this->journal->failAuthorization("error authorization.\n Please, check you phone & password");

		this->userData = employee;

		//////////////////////
		if(showEmployeeData())//вынести в новый метод
		{

		}
		else
		{
			//показать диалог повторного подключения
		}
		/////////////////
		fillTabelMarks(this->curPayForm);//create tabel
		setCurrentPeriod();

	}
	catch(log_errors::exception_states e)
	{
		QByteArray code = QString::number(this->journal->getLastErrorCode()).toLocal8Bit();
		QByteArray msg = this->journal->getLastError().toLocal8Bit();

		error_msg(code.data(),msg.data());//cообщили об ошибке
		this->journal->lastConflictNonResolved();
	}

	connect(this->ui.BillingPeriod_dateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(showPeriod(QDate)));

	connect(this->ui.GoToCurrentPeriod_button,SIGNAL(pressed()),this,SLOT(setCurrentPeriod()));
	connect(this->ui.editBtn,SIGNAL(pressed()),this,SLOT(editMarksList()));
	connect(this->ui.CancelLaborBtn,SIGNAL(pressed()),this,SLOT(cancelMarksList()));
	connect(this->ui.saveEditedLaborBtn,SIGNAL(pressed()),this,SLOT(saveMarksList()));
}

EmployeeSC::~EmployeeSC()
{
	this->journal->~log_errors();
	this->userData->~Employee();
}

void EmployeeSC::initialDBManager(QString &dbName)
{
	DbManager& manager = DbManager::manager(dbName);
    if(manager.checkConnection())
    {
        //Создание таблиц
        bool table_created = Employee::createDbTable();
        if(!table_created)
        {

        }
        table_created = BillingPeriod::createDbTable();
        if(!table_created)
        {

        }
        table_created = DutyChart::createDbTable();
        if(!table_created)
        {

        }
        table_created = LaborSheet::createDbTable();
        if(!table_created)
        {

        }
        table_created = HireDirective::createDbTable();
        if(!table_created)
        {

        }
		// должно быть вызвано после создания DutyChart и LaborSheet (из-за внешних ключей)
        table_created = Mark::createDbTable();
        if(!table_created)
        {

        }
        
		// позже это должно выполняться при создании предприятия
		initalSetupForTableDutyChart();
    }
	else
	{
		//TODO
	}
}

void EmployeeSC::error_msg(const char* short_description, const char* text)
{
	QTextCodec* c = QTextCodec::codecForLocale();
	QMessageBox::critical(NULL,c->toUnicode(short_description), c->toUnicode(text));
}

bool EmployeeSC::showEmployeeData()
{
	try
	{
		if(!this->userData->fetch()) throw this->journal->fetchError("Data pizdata");

		HireDirective *hd = new HireDirective(this->userData->hireDirectiveID());
		if(!hd->fetch()) throw this->journal->fetchError("parseDataObject hiredirective fetch error");

		DutyChart *userDutyChart = new DutyChart(this->userData->currentDutyChartID());
		if(!userDutyChart->fetch()) throw this->journal->fetchError("parseDataObject hiredirective fetch error");

		this->currentPeriod = BillingPeriod::getCurrentPeriod();
		if(!currentPeriod) throw this->journal->nullPtr("showEmployeeData billingperiod");

		parseBaseDataObject(hd,userDutyChart->name(),this->currentPeriod);

		this->curPayForm = hd->payForm();

		return true;
	}
	catch(log_errors::exception_states e)
	{
		QByteArray code = QString::number(this->journal->getLastErrorCode()).toLocal8Bit();
		QByteArray msg = this->journal->getLastError().toLocal8Bit();

		error_msg(code.data(),msg.data());//cообщили об ошибке
		this->journal->lastConflictNonResolved();

		return false;
	}
}

void EmployeeSC::parseBaseDataObject(HireDirective *hd, QString dutyChartName,BillingPeriod *currentPeriod)
{
	ui.eFIO->setText(this->userData->fio());
	ui.eNumberPhone->setText(this->userData->phoneNumber());
	ui.INN->setText(QString::number(this->userData->inn()));

	ui.ePayFormChoice->setCurrentIndex(hd->payForm()==PER_MONTH ? 0 : 1);
	ui.eReceiptDate->setDate(hd->hireDate());
	ui.eOrderNum->setText(QString::number(hd->id()));
	ui.eSalary->setValue(hd->salary());

	QPair<QDate,QDate>minmaxDate = currentPeriod->getDateSpan();
	ui.BillingPeriod_dateEdit->setMinimumDate(minmaxDate.first);
	ui.BillingPeriod_dateEdit->setMaximumDate(minmaxDate.second);

	ui.CurrentPeriod_dateEdit->setDate(currentPeriod->startDate());
	ui.BillingPeriod_dateEdit->setDate(currentPeriod->startDate());

	ui.eDutyChart->setText(dutyChartName);
}

void EmployeeSC::fillTabelMarks(PayForm pf)
{
	for(int i=0; i<ui.laborSheet->rowCount();++i)
	{
		for(int j=0; j<ui.laborSheet->columnCount();++j)
		{
			QComboBox* combo = new QComboBox();

			QTextCodec* codec = QTextCodec::codecForLocale();

			if(pf==PayForm::PER_MONTH)
			{
				combo->insertItem(0, codec->toUnicode("-"),QVariant((int)Mark::Type::INVALID));
				combo->insertItem(1, codec->toUnicode("был"),QVariant((int)Mark::Type::ATTENDS));
				combo->insertItem(2, codec->toUnicode("не был"),QVariant((int)Mark::Type::MISS));
				combo->insertItem(3, codec->toUnicode("выходной"),QVariant((int)Mark::Type::HOLIDAY));
			}
			else
			{
				for(int v=0;v<9;++v) 
					combo->insertItem(v, QString::number(v),QVariant(v));
			}


			combo->setCurrentIndex(1);

			QLabel *l = new QLabel(QString());

			QHBoxLayout *hl = new QHBoxLayout();

			hl->addWidget(l);
			hl->addWidget(combo);

			QWidget *w = new QWidget();
			w->setLayout(hl);

			ui.laborSheet->setCellWidget(i,j,w);
		}
	}
	ui.laborSheet->resizeColumnsToContents();
	ui.laborSheet->resizeRowsToContents();
}

void EmployeeSC::fillTabelDateValues(QDate &date)
{
	QDate d(date.year(),date.month(),1);
	int firstWeekDay = d.dayOfWeek();
	int countDays = d.daysInMonth();
	int lastDayOfWeek;

	bool done = false;

	int lastWeekOfMonth;
	//fill main part
	for(int i=0; i<ui.laborSheet->rowCount() && !done;++i)
	{
		for(int j=(i==0 ? firstWeekDay-1 : 0); j<ui.laborSheet->columnCount() && !done;++j)
		{
			QWidget *w =ui.laborSheet->cellWidget(i,j);

			QList<QLabel*>labelList = w->findChildren<QLabel*>();
			QList<QComboBox*>comboBoxList = w->findChildren<QComboBox*>();

			comboBoxList[0]->setVisible(true);

			labelList[0]->setText(QString::number(d.day()));
			d = d.addDays(1);

			comboBoxList[0]->setCurrentIndex(1);

			done = (i*7-firstWeekDay+j+2) == countDays;
			if(done) {lastWeekOfMonth=i+1;lastDayOfWeek=j+1;}
		}
	}
	//fill right part
	int nextMonthValues = 1;
	for(int i=lastWeekOfMonth-1; i<ui.laborSheet->rowCount();++i)
	{
		for(int j= (i==lastWeekOfMonth-1 ? lastDayOfWeek : 0); j<ui.laborSheet->columnCount();++j)
		{
			QWidget *w =ui.laborSheet->cellWidget(i,j);

			QList<QLabel*>labelList = w->findChildren<QLabel*>();
			QList<QComboBox*>comboBoxList = w->findChildren<QComboBox*>();

			comboBoxList[0]->setVisible(false);

			labelList[0]->setText(QString::number(nextMonthValues));

			comboBoxList[0]->setCurrentIndex(0);

			nextMonthValues++;
		}
	}
	//fill left part
	int prevCountDaysOfWeek = QDate(date.year(),date.month(),1).daysInMonth()-firstWeekDay+1;
	for(int j= 0; j<firstWeekDay-1;++j)
	{
		QWidget *w =ui.laborSheet->cellWidget(0,j);

		QList<QLabel*>labelList = w->findChildren<QLabel*>();
		QList<QComboBox*>comboBoxList = w->findChildren<QComboBox*>();

		comboBoxList[0]->setVisible(false);

		labelList[0]->setText(QString::number(prevCountDaysOfWeek));

		comboBoxList[0]->setCurrentIndex(0);

		prevCountDaysOfWeek++;
	}
}

void EmployeeSC::showPeriod(QDate date)
{
	try
	{
		BillingPeriod* period = BillingPeriod::getByDate(date);
		if(!period->fetch()) throw this->journal->fetchError("showPeriod BillingPeriod fetch");

		LaborSheet *lsh = new LaborSheet(this->userData->id(),period->id());
		if(!lsh->fetch(this->userData->id(),period->id())) throw this->journal->fetchError("showPeriod LaborSheet fetch");

		if(period->status()!=BillingPeriod::Status::OPEN){ui.editBtn->setEnabled(false);}
		else{ui.editBtn->setEnabled(true);}

		fillTabelDateValues(date);
		fillTabelMarksValues(date);
		setDescription(*lsh);
	}
	catch(log_errors::exception_states e)
	{
		QByteArray code = QString::number(this->journal->getLastErrorCode()).toLocal8Bit();
		QByteArray msg = this->journal->getLastError().toLocal8Bit();

		error_msg(code.data(),msg.data());//cообщили об ошибке
		this->journal->lastConflictNonResolved();
	}
}

void EmployeeSC::fillTabelMarksValues(QDate &date)
{
	try
	{
        BillingPeriod *bp = BillingPeriod::getByDate(date);
		if(!bp->fetch())throw this->journal->fetchError("EmployeeSC::fillTabelMarksValues BillingPeriod fetch");

		LaborSheet *lsh = new LaborSheet(this->userData->id(), bp->id());
		if(!lsh->fetch(this->userData->id(),bp->id()))throw this->journal->fetchError("EmployeeSC::fillTabelMarksValues LaborSheet fetch");

		QList<Mark> marks = lsh->grid();

		//#set marks
		auto i_marks = marks.begin();
		for(int i=0; i<ui.laborSheet->rowCount();++i)
		{
			i_marks++;
			for(int j=0; j<ui.laborSheet->columnCount();++j)
			{
				QWidget *w =ui.laborSheet->cellWidget(i,j);

				QList<QComboBox*>comboBoxList = w->findChildren<QComboBox*>();

				if(comboBoxList[0]->isVisible())
				{
					int tm = i_marks->altered()==Mark::Type::INVALID ? i_marks->base() : i_marks->altered();
					comboBoxList[0]->setCurrentIndex(comboBoxList[0]->findData(QVariant(tm)));
				}
			}
		}
		//#
	}
	catch(log_errors::exception_states e)
	{
		QByteArray code = QString::number(this->journal->getLastErrorCode()).toLocal8Bit();
		QByteArray msg = this->journal->getLastError().toLocal8Bit();

		error_msg(code.data(),msg.data());//cообщили об ошибке
		this->journal->lastConflictNonResolved();
	}
}

void EmployeeSC::setDescription(LaborSheet& laborSheet)
{
	ui.Description_table->clearContents();

	while(ui.Description_table->rowCount() > 0)
		ui.Description_table->removeRow(0);

	foreach(LaborSheetDescriptionLine dl, laborSheet.description())
	{
		int rows = ui.Description_table->rowCount();
		ui.Description_table->insertRow( rows );
		ui.Description_table->setVerticalHeaderItem(rows, new QTableWidgetItem(dl.name) );
		ui.Description_table->setItem(rows, 0, new QTableWidgetItem(dl.default_value) );
		//ui->Description_table->setItem(rows, 1, new QTableWidgetItem(dl.base_value) );
		ui.Description_table->setItem(rows, 1, new QTableWidgetItem(dl.altered_value) );
	}
}

void EmployeeSC::setCurrentPeriod()
{
	ui.editBtn->setEnabled(true);
	fillTabelDateValues((QDate)this->currentPeriod->startDate());
	fillTabelMarksValues((QDate)this->currentPeriod->startDate());
}

void EmployeeSC::editMarksList()
{
	ui.editBtn->setEnabled(false);
	ui.BillingPeriod_dateEdit->setEnabled(false);

	ui.laborSheet->setEnabled(true);
	ui.saveEditedLaborBtn->setEnabled(true);
	ui.CancelLaborBtn->setEnabled(true);
	ui.GoToCurrentPeriod_button->setEnabled(true);
}

void EmployeeSC::saveMarksList()
{

}

void EmployeeSC::cancelMarksList()
{
	ui.editBtn->setEnabled(true);
	ui.BillingPeriod_dateEdit->setEnabled(true);

	ui.laborSheet->setEnabled(false);
	ui.saveEditedLaborBtn->setEnabled(false);
	ui.CancelLaborBtn->setEnabled(false);
	ui.GoToCurrentPeriod_button->setEnabled(false);

	fillTabelMarksValues((QDate)this->currentPeriod->startDate());
}
