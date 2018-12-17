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
				throw this->journal->failAuthorization("Error authorization.\n Please, check you phone & password");

		this->userData = employee;


		if(showEmployeeData())
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

<<<<<<< HEAD
		//error_msg(code.data(),msg.data());//cообщили об ошибке -> перенесено в диалог входа
<<<<<<< HEAD
=======
>>>>>>> 2f6c246... hello
		error_msg(code.data(),msg.data());//cообщили об ошибке //xyi-> перенесено в диалог входа (не надо так делать)
		this->journal->lastConflictNonResolved();
<<<<<<< HEAD

		if(e==log_errors::exception_states::AUTH_EX) this->destroy();
<<<<<<< HEAD

=======
>>>>>>> 02233dc... СЃСѓРєР°
		// throw again
		throw e;
=======
>>>>>>> fa493b5... Р”РѕР±Р°РІРёР» РїРѕР»Рµ РґР»СЏ РІРІРѕРґР° РїР°СЂРѕР»СЏ
=======
		this->journal->lastConflictNonResolved();

		// throw again
		throw e;
>>>>>>> b70baee... РЎРѕРѕР±С‰РµРЅРёРµ РѕР± РѕС€РёР±РєРµ Р°РІС‚РѕСЂРёР·Р°С†РёРё РїРѕР»СЊР·РѕРІР°С‚РµР»СЏ РЅР° СЂСѓСЃСЃРєРѕРј
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


Employee* EmployeeSC::shapeDataObject()
{
	return NULL;
}

void EmployeeSC::parseDataObject(Employee *obj)
{

}

void EmployeeSC::updateInfo(QString name)
{

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
		ui.eDutyChart->setText(dutyChartName);
	}
	catch(log_errors::exception_states e)
	{
		QByteArray code = QString::number(this->journal->getLastErrorCode()).toLocal8Bit();
		QByteArray msg = this->journal->getLastError().toLocal8Bit();

		error_msg(code.data(),msg.data());//cообщили об ошибке
		this->journal->lastConflictNonResolved();

<<<<<<< HEAD
		if(e==log_errors::exception_states::AUTH_EX) {QCloseEvent *e = new QCloseEvent();e->setAccepted(true);this->closeEvent(e);this->close();}
<<<<<<< HEAD

		this->isWork= false;//

=======
>>>>>>> fa493b5... Р”РѕР±Р°РІРёР» РїРѕР»Рµ РґР»СЏ РІРІРѕРґР° РїР°СЂРѕР»СЏ
=======
		this->isWork= false;//
>>>>>>> 02233dc... СЃСѓРєР°
	}
}

void EmployeeSC::fillTabelMarks(PayForm pf)
{
	for(int i=0; i<ui.laborSheet->rowCount();++i)
	{
		for(int j=0; j<ui.laborSheet->columnCount();++j)
		{
			QComboBox* combo = new QComboBox();

			QTextCodec* codec = QTextCodec::codecForLocale();

			if(pf==PER_MONTH)
			{
				//combo->insertItem(0, codec->toUnicode("-"),QVariant((int)Mark::Type::INVALID));
				combo->insertItem(1, codec->toUnicode("был"),QVariant((int)Mark::Type::ATTENDS));
				combo->insertItem(2, codec->toUnicode("не был"),QVariant((int)Mark::Type::MISS));
				combo->insertItem(3, codec->toUnicode("выходной"),QVariant((int)Mark::Type::HOLIDAY));

				combo->setCurrentIndex(1);
			}
			else
			{
				for(int v=MAX_WORKING_COUNT_HOURS;v>=0;--v) 
					combo->insertItem(MAX_WORKING_COUNT_HOURS-v, QString::number(v),QVariant(v));

				combo->setCurrentIndex(0);
			}

			QLabel *l = new QLabel(QString());

			QHBoxLayout *hl = new QHBoxLayout();

			hl->addWidget(l);
			hl->addWidget(combo);

			QWidget *w = new QWidget(ui.laborSheet);
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

			comboBoxList[0]->setHidden(false);

			labelList[0]->setText(QString::number(d.day()));
			d = d.addDays(1);

			if(this->curPayForm==PayForm::PER_MONTH)
				comboBoxList[0]->setCurrentIndex(comboBoxList[0]->findData(QVariant(Mark::Type::ATTENDS)));
			if(this->curPayForm==PayForm::PER_HOUR)
				comboBoxList[0]->setCurrentIndex(comboBoxList[0]->findData(QVariant(MAX_WORKING_COUNT_HOURS)));

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

			comboBoxList[0]->setHidden(true);

			labelList[0]->setText(QString::number(nextMonthValues));

			/*if(this->curPayForm==PayForm::PER_MONTH)
				comboBoxList[0]->setCurrentIndex(comboBoxList[0]->findData(QVariant(Mark::Type::INVALID)));
			if(this->curPayForm==PayForm::PER_HOUR)
				comboBoxList[0]->setCurrentIndex(comboBoxList[0]->findData(QVariant(0)));*/

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

		comboBoxList[0]->setHidden(true);

		labelList[0]->setText(QString::number(prevCountDaysOfWeek));

		/*if(this->curPayForm==PayForm::PER_MONTH)
				comboBoxList[0]->setCurrentIndex(comboBoxList[0]->findData(QVariant(Mark::Type::INVALID)));
		if(this->curPayForm==PayForm::PER_HOUR)
			comboBoxList[0]->setCurrentIndex(comboBoxList[0]->findData(QVariant(0)));*/

		prevCountDaysOfWeek++;
	}
}

void EmployeeSC::showPeriod(QDate date)
{
	try
	{
		QDate d(date.year(),date.month(),1);
		BillingPeriod* period = BillingPeriod::getByDate(d);
		if(!period->fetch()) throw this->journal->fetchError("showPeriod getByDate BillingPeriod fetch");

		LaborSheet *lsh = new LaborSheet(this->userData->id(),period->id());
		if(!lsh->fetch(this->userData->id(),period->id())) throw this->journal->fetchError("showPeriod LaborSheet fetch");

		if(period->status()!=BillingPeriod::Status::OPEN){ui.editBtn->setEnabled(false);ui.GoToCurrentPeriod_button->setEnabled(true);}
		else{ui.editBtn->setEnabled(true);ui.GoToCurrentPeriod_button->setEnabled(false);}

		fillTabelDateValues(d);
		fillTabelMarksValues(d);
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
		if(!bp->fetch())throw this->journal->fetchError("fillTabelMarksValues getByDate BillingPeriod fetch");
       BillingPeriod *bp = BillingPeriod::getByDate(date);
		if(!bp->fetch())throw this->journal->fetchError("EmployeeSC::fillTabelMarksValues BillingPeriod fetch");
		LaborSheet *lsh = new LaborSheet(this->userData->id(), bp->id());
		if(!lsh->fetch(this->userData->id(),bp->id()))throw this->journal->fetchError("EmployeeSC::fillTabelMarksValues LaborSheet fetch");

		QList<Mark> marks = lsh->grid();
		if(marks.empty()) throw this->journal->nullPtr("data about marks not found");

		//#set marks
		auto i_marks = marks.begin();
		for(int i=0; i<ui.laborSheet->rowCount() && i_marks != marks.end();++i)
		{
			for(int j=0; j<ui.laborSheet->columnCount() && i_marks != marks.end();++j)
			{
				QWidget *w =ui.laborSheet->cellWidget(i,j);

				QList<QComboBox*>comboBoxList = w->findChildren<QComboBox*>();

				if(!comboBoxList[0]->isHidden())
				{
					int tm;

					if(this->curPayForm==PayForm::PER_MONTH)
						tm = i_marks->altered()==Mark::Type::INVALID ? i_marks->base() : i_marks->altered();
					else
<<<<<<< HEAD
<<<<<<< HEAD
						tm = i_marks->alteredCountHours()==-1 ? i_marks->countHours() : i_marks->alteredCountHours();
=======
						tm = i_marks->altered()==Mark::Type::INVALID ? i_marks->countHours() : i_marks->alteredCountHours();
>>>>>>> f9c5f82... СЃРѕС…СЂР°РЅРµРЅРёРµ РЅРµ СЂРѕР±РёС‚, РІСЃРµ РѕСЃС‚Р°Р»СЊРЅРѕРµ СЂРѕР±РёС‚
=======
						tm = i_marks->alteredCountHours()==-1 ? i_marks->countHours() : i_marks->alteredCountHours();
>>>>>>> 1413454... РјРµС‚РѕРґ СЃРѕС…СЂР°РЅРµРЅРёСЏ РѕС‚РјРµС‚РѕРє СЂРѕР±РёС‚

					comboBoxList[0]->setCurrentIndex(comboBoxList[0]->findData(QVariant(tm)));
					i_marks++;
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
	ui.GoToCurrentPeriod_button->setEnabled(false);
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
	//LaborSheet *lsh = new LaborSheet();
	try
<<<<<<< HEAD
	{
		BillingPeriod *bp = this->currentPeriod;//BillingPeriod::getByDate(ui.BillingPeriod_dateEdit->date());
			//if(!bp->fetch())throw this->journal->fetchError("saveMarksList getByDate BillingPeriod fetch");

		LaborSheet *lsh = new LaborSheet(this->userData->id(), bp->id());
			if(!lsh->fetch(this->userData->id(),bp->id()))throw this->journal->fetchError("saveMarksList  LaborSheet fetch");

		QList<Mark> ms;
		const QList<Mark> oldMS = lsh->grid();
		if(oldMS.empty()) throw this->journal->nullPtr("saveMarksList data about marks not found");

		int counter = 0;
		for(int i=0; i<ui.laborSheet->rowCount();++i)
		{
			for(int j=0; j<ui.laborSheet->columnCount();++j)
			{
				QWidget *w =ui.laborSheet->cellWidget(i,j);

				QList<QLabel*>labelList = w->findChildren<QLabel*>();
				QList<QComboBox*>comboBoxList = w->findChildren<QComboBox*>();

				if(!comboBoxList[0]->isHidden())
				{
					if(counter>=oldMS.count())throw this->journal->compareError("soory, bitch");

					Mark *m = new Mark();
					int data = comboBoxList[0]->currentData().toInt();
						
					if(this->curPayForm == PayForm::PER_MONTH) 
						(oldMS[counter].base()!=data ? m->setAlteredMark(data) : m->setBaseMark(data));

					if(this->curPayForm == PayForm::PER_HOUR) 
						(oldMS[counter].countHours()!=data ? m->setAlteredCountHours(data) : m->setCountHours(data));

					m->setId(oldMS[counter].id());

					ms.append(*m);
					counter++;
				}
			}
		}

		lsh->setGrid(ms);

		if(!lsh->update()) throw this->journal->updateError("sorry, bitch");

		ui.editBtn->setEnabled(true);
	}
	catch(log_errors::exception_states e)
	{
		QByteArray code = QString::number(this->journal->getLastErrorCode()).toLocal8Bit();
		QByteArray msg = this->journal->getLastError().toLocal8Bit();

		error_msg(code.data(),msg.data());//cообщили об ошибке
		this->journal->lastConflictNonResolved();
	}

	ui.BillingPeriod_dateEdit->setEnabled(true);

	ui.laborSheet->setEnabled(false);
	ui.saveEditedLaborBtn->setEnabled(false);
	ui.CancelLaborBtn->setEnabled(false);
	ui.GoToCurrentPeriod_button->setEnabled(false);
	QMessageBox::information(NULL,"Success", "Data saved complete!");

	QList<Mark*> m;
	int currentDay = QDate::currentDate().day();
	for(int i=0; i<ui.laborSheet->rowCount();++i)
=======
>>>>>>> f9c5f82... СЃРѕС…СЂР°РЅРµРЅРёРµ РЅРµ СЂРѕР±РёС‚, РІСЃРµ РѕСЃС‚Р°Р»СЊРЅРѕРµ СЂРѕР±РёС‚
	{
		BillingPeriod *bp = this->currentPeriod;//BillingPeriod::getByDate(ui.BillingPeriod_dateEdit->date());
			//if(!bp->fetch())throw this->journal->fetchError("saveMarksList getByDate BillingPeriod fetch");

		LaborSheet *lsh = new LaborSheet(this->userData->id(), bp->id());
			if(!lsh->fetch(this->userData->id(),bp->id()))throw this->journal->fetchError("saveMarksList  LaborSheet fetch");

		QList<Mark> ms;
		const QList<Mark> oldMS = lsh->grid();
		if(oldMS.empty()) throw this->journal->nullPtr("saveMarksList data about marks not found");

		int counter = 0;
		for(int i=0; i<ui.laborSheet->rowCount();++i)
		{
			for(int j=0; j<ui.laborSheet->columnCount();++j)
			{
				QWidget *w =ui.laborSheet->cellWidget(i,j);

				QList<QLabel*>labelList = w->findChildren<QLabel*>();
				QList<QComboBox*>comboBoxList = w->findChildren<QComboBox*>();

				if(!comboBoxList[0]->isHidden())
				{
					if(counter>=oldMS.count())throw this->journal->compareError("soory, bitch");

					Mark *m = new Mark();
					int data = comboBoxList[0]->currentData().toInt();
						
					if(this->curPayForm == PayForm::PER_MONTH) 
						(oldMS[counter].base()!=data ? m->setAlteredMark(data) : m->setBaseMark(data));

					if(this->curPayForm == PayForm::PER_HOUR) 
						(oldMS[counter].countHours()!=data ? m->setAlteredCountHours(data) : m->setCountHours(data));

					ms.append(*m);
					counter++;
				}
			}
		}

		lsh->setGrid(ms);

		if(!lsh->update()) throw this->journal->updateError("sorry, bitch");

		ui.editBtn->setEnabled(true);
	}
<<<<<<< HEAD

=======
	catch(log_errors::exception_states e)
	{
		QByteArray code = QString::number(this->journal->getLastErrorCode()).toLocal8Bit();
		QByteArray msg = this->journal->getLastError().toLocal8Bit();

		error_msg(code.data(),msg.data());//cообщили об ошибке
		this->journal->lastConflictNonResolved();
	}

	ui.BillingPeriod_dateEdit->setEnabled(true);

	ui.laborSheet->setEnabled(false);
	ui.saveEditedLaborBtn->setEnabled(false);
	ui.CancelLaborBtn->setEnabled(false);
	ui.GoToCurrentPeriod_button->setEnabled(false);
	QMessageBox::information(NULL,"Success", "Data saved complete!");
>>>>>>> f9c5f82... СЃРѕС…СЂР°РЅРµРЅРёРµ РЅРµ СЂРѕР±РёС‚, РІСЃРµ РѕСЃС‚Р°Р»СЊРЅРѕРµ СЂРѕР±РёС‚
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
