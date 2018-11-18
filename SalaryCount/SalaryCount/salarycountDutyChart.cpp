#include "salarycountDutyChart.h"

salarycountDutyChart::salarycountDutyChart(Ui_SalaryCount* ui, QString name)
	:delegateStates()
{
	this->setObjectName(name);
	this->ui = ui;//не самый приятный способ

	this->ui->editDutyChart->setEnabled(false);
	this->ui->deleteDutyChart->setEnabled(false);

	for(int i=0; i<ui->DutyChartMarksEdit->rowCount();++i)
	{
		QComboBox* combo = new QComboBox();

		QTextCodec* codec = QTextCodec::codecForLocale();

		combo->insertItem(0, codec->toUnicode("Выходной"));
		combo->insertItem(1, codec->toUnicode("Рабочий"));

		combo->setCurrentIndex(1);

		ui->DutyChartMarksEdit->setCellWidget(i,0,combo);
	}

	//работа с графиками
	ui->saveDutyChartBtn->setEnabled(true);
	ui->cancelDutyChartBtn->setEnabled(true);

	connect(ui->addDutyChart,SIGNAL(pressed()), SLOT(addDutyChart()));
	connect(ui->editDutyChart,SIGNAL(pressed()), SLOT(editDutyChart()));
	connect(ui->cancelDutyChartBtn,SIGNAL(pressed()), SLOT(cancelNewDutyChart()));
	connect(ui->saveDutyChartBtn,SIGNAL(pressed()),this,SLOT(saveNewDutyChart()));
	connect(ui->deleteDutyChart,SIGNAL(pressed()), SLOT(deleteDutyChart()));

	connect(ui->payFormChoice,SIGNAL(currentIndexChanged(int)), SLOT(changePayForm(int)));
	connect(ui->dutyChartList,SIGNAL(currentRowChanged(int)), SLOT(showSelectedItem(int)));
}

salarycountDutyChart::~salarycountDutyChart()
{
	this->ui = NULL;
	delete this->journal;
}

void salarycountDutyChart::switchMode(app_states state)
{
	this->currentState = state;//запомним состояние приложения

	//приведем состояние к булеву типу для посылки главному окну
	bool triggerState = false;
	if(state!=app_states::USUAL)
	{
		triggerState = true;
	}

	//изменение состояния окна
	ui->dutyChartEdit->setEnabled(triggerState);
	ui->dutyChartBox->setEnabled(!triggerState);

	emit changeState(triggerState);//посылка состояния в родительское окно
}

/*!
*\
*/
void salarycountDutyChart::addDutyChart()
{
	switchMode(app_states::ADD);
	clearFields();//clear fields

	ui->dutyChartList->setCurrentRow(-1);
}

void salarycountDutyChart::editDutyChart()
{
	switchMode(app_states::EDIT);
}

/*!
*\
*/
void salarycountDutyChart::cancelNewDutyChart()
{
	switchMode(app_states::USUAL);

	int row = ui->dutyChartList->currentRow();
	if(row!=-1)
	{ 
		showSelectedItem(row);
	}
	else
	{
		clearFields();//clear fields
	}
}

void salarycountDutyChart::deleteDutyChart()
{
	try
	{
		int row = ui->dutyChartList->currentRow();
		int countItems = ui->dutyChartList->count();

		if(row<0 && countItems<=row) throw this->journal->notFound("Элемент виджета не найден");

		//
		int ID = ui->dutyChartList->item(row)->type();
		DutyChart curChart(ID);

		if(!curChart.delet()) throw this->journal->deletError("Удаление виджета не произошло");

		//
		if(countItems!=1 && row!=0) ui->dutyChartList->setCurrentRow(row-1);
		if(countItems!=1 && row+1!=countItems) ui->dutyChartList->setCurrentRow(row+1);
		if(countItems==1) ui->dutyChartList->setCurrentRow(-1);

		delete ui->dutyChartList->takeItem(row);
	}
	catch(log_errors::exception_states e)
	{
		//
		QByteArray code = QString::number(this->journal->getLastErrorCode()).toLocal8Bit();
		QByteArray msg = this->journal->getLastError().toLocal8Bit();

		error_msg(code.data(),msg.data());//cообщили об ошибке
		this->journal->lastConflictNonResolved();
	}
}

void salarycountDutyChart::saveNewDutyChart()
{
	DutyChart* obj = shapeDataObject();//собрать данные

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

void salarycountDutyChart::saveNewEntries(DutyChart* obj)
{
	try
	{
		int ID;

		//
		if(this->currentState != app_states::ADD) 
			throw this->journal->compareError("Значения состояния для сохранения не совпадает с состоянием приложения");
		if(!obj) throw this->journal->nullPtr("Объект для сохранения не существует");
		if(!obj->validate()) throw this->journal->validateError("Валидация записи не успешна");
		if((ID = obj->insert())==-1) throw this->journal->insertError("Запись не дошла в бд");

		//добавить значение в конец списка
		QListWidgetItem *item = new QListWidgetItem(obj->name(), ui->dutyChartList, ID);
		ui->dutyChartList->addItem(item);

		ui->dutyChartList->setCurrentRow(ui->dutyChartList->count()-1);
		switchMode(app_states::USUAL);
	}
	catch(log_errors::exception_states e)
	{
		if(log_errors::exception_states::VALIDATE_EX)
		{
			//достать ошибку из объекта
			//показать пользователю
			this->journal->lastConflictResolved();
		}
		else
		{
			QByteArray code = QString::number(this->journal->getLastErrorCode()).toLocal8Bit();
			QByteArray msg = this->journal->getLastError().toLocal8Bit();

			error_msg(code.data(),msg.data());//cообщили об ошибке
			this->journal->lastConflictNonResolved();
		}
	}
}

void salarycountDutyChart::saveEditableEntries(DutyChart* obj)
{
	try
	{
		//
		if(this->currentState != app_states::EDIT) 
			throw this->journal->compareError("Значения состояния для сохранения не совпадает с состоянием приложения");
		if(!obj) throw this->journal->nullPtr("Объект для сохранения не существует");
		if(!obj->validate()) throw this->journal->validateError("Валидация записи не успешна");
		if(!obj->update()) throw this->journal->updateError("Запись не дошла в бд");

		//
		switchMode(app_states::USUAL);

		QListWidgetItem *item = ui->dutyChartList->currentItem();
		if(item) item->setText(obj->name());
	}
	catch(log_errors::exception_states e)
	{
		if(log_errors::exception_states::VALIDATE_EX)
		{
			//достать ошибку из объекта
			//показать пользователю
			this->journal->lastConflictResolved();
		}
		else
		{
			QByteArray code = QString::number(this->journal->getLastErrorCode()).toLocal8Bit();
			QByteArray msg = this->journal->getLastError().toLocal8Bit();

			error_msg(code.data(),msg.data());//cообщили об ошибке
			this->journal->lastConflictNonResolved();
		}
	}
}

DutyChart* salarycountDutyChart::shapeDataObject()
{
	int id = 0;//в зависимости от состояния редактирования запомнит ID
    
	DutyChart* obj = NULL;
	const QList<Mark> *grid = NULL;
	if(this->currentState == app_states::EDIT)
	{
		id = ui->dutyChartList->currentItem()->type();
		obj = new DutyChart(id);

		if(!obj->fetch()) throw this->journal->fetchError("Не сфетчилось что-то((");

		grid = &obj->grid();
	}

	QString name = ui->nameDutyChart->text();//занести имя
	QDate ancDate = ui->startDate->date();//запомнить якорную дату
	PayForm pf = (ui->payFormChoice->currentIndex()==0 ? PayForm::PER_MONTH : PayForm::PER_HOUR);//запомнить платежную форму
	QTime workTime(ui->workTimeEdit->time());//в зависимости от платежной формы запомнить рабочее время

	//запомнить отметки
	//разбить бы на отдельный метод
	//даже трогать не хочу это))
	QList<Mark> *ms = new QList<Mark>();
	for(int i=0; i< this->ui->DutyChartMarksEdit->rowCount(); ++i)
	{
		QComboBox* combo = (QComboBox*)ui->DutyChartMarksEdit->cellWidget(i,0);

		Mark *m = NULL;

		switch(pf)
		{
			case PayForm::PER_MONTH:
				m = new Mark( (combo->currentIndex()==1 ? 
					Mark::ATTENDS : Mark::HOLIDAY),NULL,NULL,NULL,id,NULL );
				m->setId((grid ? grid->at(i).id():NULL));
				break;

			case PayForm::PER_HOUR:
				m = new Mark( NULL,NULL,(combo->currentIndex()==1 ? 
					ui->workTimeEdit->time().hour() : Mark::HOLIDAY),NULL,id, NULL );
					m->setId((grid ? grid->at(i).id():NULL));
				break;

			default:
				throw this->journal->nullPtr();
		}
			
		ms->append(*m);
		delete m;
	}

	obj = new DutyChart(name,*ms,ancDate,pf);
	delete ms;

	return obj;
}

void salarycountDutyChart::changePayForm(int index)
{
	if(index)
	{
		ui->workTimeEdit->setMinimumTime(QTime(1,0));
		ui->workTimeEdit->setEnabled(true);

	}
	else
	{
		ui->workTimeEdit->setMinimumTime(QTime(0,0));
		ui->workTimeEdit->setEnabled(false);
		ui->workTimeEdit->setTime(QTime(0,0));
	}
}

void salarycountDutyChart::clearFields()
{
	this->ui->nameDutyChart->clear();
	this->ui->startDate->setDateTime(QDateTime(QDate::currentDate()));
	this->ui->workTimeEdit->setTime(QTime(0,0));

	for(int i=this->ui->DutyChartMarksEdit->rowCount()-1; i>=0; --i)
	{
		QComboBox* combo = (QComboBox*)ui->DutyChartMarksEdit->cellWidget(i,0);
		
		if(combo->count()>=2)
		{
			combo->setCurrentIndex(1);
		}
	}

	if(this->ui->payFormChoice->count()>=1)
	{
		this->ui->payFormChoice->setCurrentIndex(0);
	}
}

void salarycountDutyChart::updateInfo(QString name)
{
	if(!this->objectName().compare(name) && ui->dutyChartList->count() != DutyChart::countEntries())
	{
		QMap<int,QString> allEntries = DutyChart::getAll();
		ui->dutyChartList->clear();

		if(allEntries.count() > 0)
		{
			QList<int> &keys = allEntries.keys();
			QList<QString> &val = allEntries.values();
			qSort(keys);

			foreach(const int &iter, keys)
			{
				QString d = allEntries.value( iter );
				QListWidgetItem *item = new QListWidgetItem(allEntries.value( iter ), ui->dutyChartList, iter);
				ui->dutyChartList->addItem(item);
			}

			ui->dutyChartList->setCurrentRow(0);
		}
	}
}

void salarycountDutyChart::parseDataObject(const DutyChart *obj)
{
	if(!obj) throw this->journal->nullPtr();

	ui->nameDutyChart->setText( obj->name() );
	ui->startDate->setDate( obj->anchorDate() );

	bool isMonth = obj->payForm() == PayForm::PER_MONTH;
	ui->payFormChoice->setCurrentIndex( !isMonth );

	const QList<Mark> &m = obj->grid();

	if(!isMonth && m.count())
	{
		ui->workTimeEdit->setTime(QTime(m[0].countHours(),0));
	}

	//
	if(m.count()!=ui->DutyChartMarksEdit->rowCount())
		throw this->journal->compareError("грид не равен рабочей недели");

	for(int i=m.count()-1; i>=0; --i)
	{
		QComboBox* combo = (QComboBox*)ui->DutyChartMarksEdit->cellWidget(i,0);
		if(m[i].base() == Mark::Type::HOLIDAY || m[i].countHours() == Mark::Type::HOLIDAY)
		{
			combo->setCurrentIndex(0);
		}
		else
		{
			combo->setCurrentIndex(1);
		}
	}
}

void salarycountDutyChart::showSelectedItem( int row )
{
	clearFields();

	if(row!=-1 && ui->dutyChartList->count() > row)
	{
		int ID = ui->dutyChartList->currentItem()->type();

		DutyChart curChart( ID );

		if(!curChart.fetch()) throw this->journal->fetchError("фетч не сфетчил");
		parseDataObject(&curChart);

		this->ui->editDutyChart->setEnabled(true);
		this->ui->deleteDutyChart->setEnabled(true);
	}
	else
	{
		this->ui->editDutyChart->setEnabled(false);
		this->ui->deleteDutyChart->setEnabled(false);
    }
}