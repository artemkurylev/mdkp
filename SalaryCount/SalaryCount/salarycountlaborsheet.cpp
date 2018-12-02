#include "salarycountlaborsheet.h"
#include<qtablewidget.h>
QTableWidgetItem* makeDateLabel(int day);


salarycountLaborSheet::salarycountLaborSheet(Ui_SalaryCount *ui, QString name)
{
	this->setObjectName(name);
	this->ui = ui;//не самый приятный способ

	this->_viewedPeriod = NULL;
	
	goToCurrentPeriod();

    //Connections
	connect(ui->BillingPeriod_dateEdit,SIGNAL(dateChanged(const QDate&)), this,SLOT(periodDateChanged(const QDate&))); // обновить дату текущего периода
	connect(ui->ClosePeriod_button,SIGNAL(clicked()), this,SLOT(closePeriod())); // закрыть текущий период
	connect(ui->GoToCurrentPeriod_button,SIGNAL(clicked()), this,SLOT(goToCurrentPeriod())); // перейти на текущий период
    connect(ui->employeeLaborSheetTable,SIGNAL(currentCellChanged(int,int,int,int)),this, SLOT(showSelectedItem(int)));

    connect(ui->updateLaborBtn,SIGNAL(pressed()),SLOT(editLaborSheet()));
    connect(ui->saveEditedLaborBtn,SIGNAL(pressed()),SLOT(saveEditedLabor()));
    connect(ui->CancelLaborBtn,SIGNAL(pressed()),SLOT(cancelEditLabor()));

	ui->LabourGroupEdit->setEnabled(false);
    ui->employeeLaborSheetTable->setColumnWidth(0,0);
    /*ui->laborSheet->setMaximumWidth(500);
    ui->LabourGroupEdit->setMaximumWidth(550);*/
    for(int i = 0; i < 7;++i)
    {
        ui->laborSheet->setColumnWidth(i,75);
        
    }
}
salarycountLaborSheet::~salarycountLaborSheet()
{
	delete _viewedPeriod;
}

void salarycountLaborSheet::regenMarksCalendar()
{
    int start_day_of_week = _viewedPeriod->startDate().dayOfWeek() - 1;
    int month_length = _viewedPeriod->startDate().daysInMonth();
    int prev_month_length = _viewedPeriod->startDate().addMonths(-1).daysInMonth();
	
	// очистим таблицу с удалением виджетов
	ui->laborSheet->clearContents();
	_comboboxes.clear();

	// заполним таблицу заново...

	for(int i=0 ; i<start_day_of_week ; ++i)
	{
		// Нужно вставить лэйблы с числами до начала месяца
		int day = prev_month_length + 1 - (start_day_of_week - i);
		ui->laborSheet->setItem(i/7,i % 7, makeDateLabel(day) );
	}

	QTextCodec* codec = QTextCodec::codecForLocale();
	for(int i=start_day_of_week ; i<start_day_of_week+month_length ; ++i)
	{
		int day = i - start_day_of_week + 1;
		// Нужно вставить комбобоксы
        QComboBox* combo = new QComboBox();
		combo->insertItem(0, codec->toUnicode("-"));
		combo->insertItem(1, codec->toUnicode("--"));
		combo->setCurrentIndex(0);
		combo->setToolTip(codec->toUnicode("<html><head/><body><b>%1</b> число</body></html>").arg(day));
		_comboboxes.push_back(combo);
		ui->laborSheet->setCellWidget(i/7,i % 7, combo );
	}

	// 42 = 7 дней * 6 недель
	for(int i=start_day_of_week+month_length ; i<42 ; ++i)
	{
		// Нужно вставить лэйблы с числами после конца месяца
		int day = i - (start_day_of_week+month_length) + 1;

		ui->laborSheet->setItem(i/7,i % 7, makeDateLabel(day) );
	}
    ui->LabourGroupEdit->setEnabled(false);
    ui->employeeLaborSheetTable->setColumnWidth(0,0);
}

/*! 
\param day в диапазоне [1..31]
\returns указатель на QTableWidgetItem, который нужно будет потом удалить
*/
QTableWidgetItem* makeDateLabel(int day)
{
        QTableWidgetItem *twitem = new QTableWidgetItem( QString::number(day) );
        twitem->setTextAlignment(Qt::AlignCenter);
        twitem->setFlags(Qt::ItemIsEnabled);
        //laborSheet->setItem(0, 0, twitem);
		return twitem;
}

void salarycountLaborSheet::switchMode(app_states state)
{
	this->currentState = state;

	bool triggerState = false;
	if(state==app_states::EDIT)
	{
		triggerState = true;
	}

    ui->LabourGroupEdit->setEnabled(triggerState);
	ui->saveEditedLaborBtn->setEnabled(triggerState);
	ui->CancelLaborBtn->setEnabled(triggerState);

	emit changeState(triggerState); // может быть, лучше сделать наоборот - чтобы переключение происходило по этому сигналу ???
}
void salarycountLaborSheet::updateInfo(QString name)
{
    if(this->objectName().compare(name) != 0)
		return;

    QList<LaborSheet> labor_data = LaborSheet::getByPeriodId(_viewedPeriod->id());
        ui->employeeLaborSheetTable->clearContents();
        while(ui->employeeLaborSheetTable->rowCount() > 0)
            ui->employeeLaborSheetTable->removeRow(0);
        int row = 0;
        for(int i = 0; i < labor_data.size(); ++i)
        {
            ui->employeeLaborSheetTable->insertRow(row);
            Employee employee(*(labor_data[i].employee()));
            employee.fetch();
            ui->employeeLaborSheetTable->setItem(row,0,new QTableWidgetItem(QString(labor_data[i].id())));
            ui->employeeLaborSheetTable->setItem(row,1,new QTableWidgetItem(employee.fio()));
            ui->employeeLaborSheetTable->item(row,0)->setData(Qt::UserRole,labor_data[i].id());
			// TODO: добавить инфо по остальным столбцам (прочерки или реальные значения для закрытого месяца)
            if(labor_data[i].award() > 0)
                ui->employeeLaborSheetTable->setItem(row,2,new QTableWidgetItem(QString::number(labor_data[i].award())));
            ++row;
        }
        if(ui->employeeLaborSheetTable->rowCount() > 0)
            ui->employeeLaborSheetTable->setCurrentCell(0,1);
	//}
}

void salarycountLaborSheet::showSelectedItem(int row)
{
    QTextCodec* codec = QTextCodec::codecForLocale();
    if(row >= 0)
    {
        int id = ui->employeeLaborSheetTable->item(row,0)->data(Qt::UserRole).toInt();
        LaborSheet labor_sheet(id,0,0,QList<Mark>());
        labor_sheet.fetch();
        QList<Mark>marks = labor_sheet.grid();
        int start = _viewedPeriod->startDate().dayOfWeek() - 1;
        if(labor_sheet.payForm() == PayForm::PER_MONTH)
        {
            //int row = 0;
        
            for(int i = start;i < marks.size() + start;++i){
                QComboBox* combo = (QComboBox*)ui->laborSheet->cellWidget(i/7,i%7);
                combo->clear();
                combo->insertItem(0,codec->toUnicode("Выходной"));
                combo->insertItem(1,codec->toUnicode("Рабочий"));
                combo->insertItem(2,codec->toUnicode("Не был"));
                if(!marks[i - start].isAltered())
                {
                    switch(marks[i - start].base())
                    {
                        case Mark::HOLIDAY:
                        {
                            combo->setCurrentIndex(0);
                            break;
                        }
                        case Mark::ATTENDS:
                        {
                            combo->setCurrentIndex(1);
                            break;
                        }
                        case Mark::MISS:
                        {
                            combo->setCurrentIndex(2);
                            break;
                        }
                    }
                }
                else
                {
                    switch(marks[i - start].altered())
                    {
                        case Mark::HOLIDAY:
                        {
                            combo->setCurrentIndex(0);
                            break;
                        }
                        case Mark::ATTENDS:
                        {
                            combo->setCurrentIndex(1);
                            break;
                        }
                        case Mark::MISS:
                        {
                            combo->setCurrentIndex(2);
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            //int row = 0;
            for(int i = start;i <marks.size() + start;++i)
            {
                QComboBox* combo = (QComboBox*)ui->laborSheet->cellWidget(i/7,i%7);
                combo->clear();
                for(int j = 0; j <= 12; ++j)
                {
                    combo->insertItem(j,QString::number(j));
                }
                if(!marks[i - start].isAlteredCountHours()) 
                    combo->setCurrentIndex(marks[i - start].countHours());
                else
                    combo->setCurrentIndex(marks[i - start].alteredCountHours());
            }
        }
    }
}
void salarycountLaborSheet::periodDateChanged(const QDate& newdate)
{
	QDate date(newdate);
	if(date.day() != 1)
	{
		date.setDate(date.year(), date.month(), 1);
		ui->BillingPeriod_dateEdit->setDate(date);
	}
	if(this->_viewedPeriod->startDate() == date)
	{
		// отсеять паразитные вызовы
		return;
	}

	BillingPeriod* bp = BillingPeriod::getByDate(date);
	if(bp)
	{
		delete this->_viewedPeriod;
		this->_viewedPeriod = bp;
		ui->ClosePeriod_button->setEnabled(this->_viewedPeriod->status() == BillingPeriod::OPEN);
		ui->GoToCurrentPeriod_button->setEnabled(this->_viewedPeriod->status() != BillingPeriod::OPEN);
		regenMarksCalendar();
        updateInfo(this->objectName());
	}
	else
	{
		error_msg("Ошибка","Периода не существует");
	}
}
void salarycountLaborSheet::goToCurrentPeriod()
{
	BillingPeriod* bp = BillingPeriod::getCurrentPeriod();
	if(bp)
	{
        if(!this->_viewedPeriod)
		{
			// установить границы для DateEdit [В ПЕРВЫЙ РАЗ]
			QPair<QDate,QDate> date_span = BillingPeriod::getDateSpan();
			ui->BillingPeriod_dateEdit->setDateRange(date_span.first, date_span.second);

			this->_viewedPeriod = bp;
		    regenMarksCalendar();
        }
        ui->BillingPeriod_dateEdit->setDate(bp->startDate()); // через сигнал инициирует переход на указанный месяц
        ui->CurrentPeriod_dateEdit->setDate(bp->startDate());
		ui->ClosePeriod_button->setEnabled(true);
		ui->GoToCurrentPeriod_button->setEnabled(false);
		//regenMarksCalendar();	// обновить ячейки для отметок(Не надо, т.к. обновляются при смене даты)
	}
	else
	{
		// ERROR!
		ui->GoToCurrentPeriod_button->setText("Текущего нет?!");
	}
}
void salarycountLaborSheet::closePeriod()
{
	bool ok = BookKeeper::closeBillingPeriod(*this->_viewedPeriod);
	if(!ok)
	{
		// ERROR !!!
		ui->ClosePeriod_button->setText("Текущего нет?!");
	}
	ui->ClosePeriod_button->setEnabled(this->_viewedPeriod->status() == BillingPeriod::OPEN);
	ui->GoToCurrentPeriod_button->setEnabled(this->_viewedPeriod->status() != BillingPeriod::OPEN);

	// установить границы для DateEdit
	QPair<QDate,QDate> date_span = BillingPeriod::getDateSpan();
	ui->BillingPeriod_dateEdit->setDateRange(date_span.first, date_span.second);
    ui->CurrentPeriod_dateEdit->setDate(date_span.second);

	updateInfo(this->objectName());
        
}
void salarycountLaborSheet::editLaborSheet()
{
    switchMode(app_states::EDIT);
}
void salarycountLaborSheet::saveEditableEntries(LaborSheet* obj)
{
	if(obj->update())
	{
		switchMode(app_states::USUAL);
	}
	else
	{
		error_msg("Произошла ошибка программы","Невозможно сохранить тебель...");
	}
}
void salarycountLaborSheet::saveEditedLabor()
{
    //Тут еще валидация
    LaborSheet* labor_sheet = shapeDataObject();
    saveEditableEntries(labor_sheet);
    delete labor_sheet;
}
void salarycountLaborSheet::cancelEditLabor()
{
	switchMode(app_states::USUAL);
	showSelectedItem( ui->employeeLaborSheetTable->currentRow() );
}
LaborSheet* salarycountLaborSheet::shapeDataObject()
{
    int id = 0;
    LaborSheet* obj = NULL;
	const QList<Mark> *grid = NULL;
	if(this->currentState == app_states::EDIT)
	{
        int row = ui->employeeLaborSheetTable->currentRow();
        id = ui->employeeLaborSheetTable->item(row,0)->data(Qt::UserRole).toInt();
		QList<Mark> m;
        obj = new LaborSheet(id,0,0,m);
		obj->fetch();
        grid = &obj->grid();
	}
    int start = _viewedPeriod->startDate().dayOfWeek() - 1; 
    QList<Mark> *ms = new QList<Mark>();
    PayForm pf = obj->payForm();
    for(int i = start; i - start < grid->size(); ++i)
	{
		QComboBox* combo = (QComboBox*)ui->laborSheet->cellWidget(i/7,i%7);

		int val = 0;
        Mark* m;
        m = new Mark(grid->at(i - start));
		switch(pf)
		{
			case PayForm::PER_MONTH:
            {
                val = combo->currentIndex();
                if(val == 0)
                    val = Mark::HOLIDAY;
                else if(val == 1)
                    val = Mark::ATTENDS;
                else if(val == 2)
                    val = Mark::MISS;
				m->setAlteredMark(val); // Нужно делать так всегда
                //if(_viewedPeriod->status() == BillingPeriod::OPEN)
                //{
                //    m->setBaseMark(val);
                //}
                //else
                //{
                //    m->setAlteredMark(val);
                //}
                break;
            }

			case PayForm::PER_HOUR:
            {
                val = combo->currentIndex();
                m->setAlteredCountHours(val);
                break;
            }

			default:
				throw new nullptr_t;
		}
        ms->append(*m);
        delete m;
	}
    obj->setGrid(*ms);
	return obj;
}