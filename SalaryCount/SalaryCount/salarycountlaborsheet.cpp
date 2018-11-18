#include "salarycountlaborsheet.h"

QTableWidgetItem* makeDateLabel(int day);


salarycountLaborSheet::salarycountLaborSheet(Ui_SalaryCount *ui, QString name)
{
	this->setObjectName(name);
	this->ui = ui;//не самый приятный способ

	this->_viewedPeriod = BillingPeriod::getCurrentPeriod();
	ui->BillingPeriod_dateEdit->setDate(_viewedPeriod->startDate());
	ui->ClosePeriod_button->setEnabled(true);

    //Connections
	connect(ui->BillingPeriod_dateEdit,SIGNAL(dateChanged(const QDate&)), this,SLOT(periodDateChanged(const QDate&))); // обновить дату текущего периода
	//connect(ui->ClosePeriod_button,SIGNAL(clicked()), this,SLOT(!!!!())); // закрыть текущий период
    connect(ui->employeeLaborSheetTable,SIGNAL(currentCellChanged(int,int,int,int)),this, SLOT(showSelectedItem(int)));
    //connect(ui->editDutyChart,SIGNAL(pressed()), SLOT(editDutyChart())); Зачем здесь этот коннект??
    connect(ui->updateLaborBtn,SIGNAL(pressed()),SLOT(editLaborSheet()));
	regenMarksCalendar();	// обновить ячейки для отметок

	ui->LabourGroupEdit->setEnabled(false);
    ui->employeeLaborSheetTable->setColumnWidth(0,0);
}
salarycountLaborSheet::~salarycountLaborSheet()
{
	delete _viewedPeriod;
}

void salarycountLaborSheet::regenMarksCalendar()
{
    int startDayOfWeek = _viewedPeriod->startDate().dayOfWeek() - 1;
    int monthLength = _viewedPeriod->startDate().daysInMonth();
    int prev_month_length = _viewedPeriod->startDate().addMonths(-1).daysInMonth();
	
	// очистим таблицу с удалением виджетов
	ui->laborSheet->clearContents();
	_comboboxes.clear();

	// заполним таблицу заново...

	for(int i=0 ; i<startDayOfWeek ; ++i)
	{
		// Нужно вставить лэйблы с числами до начала месяца
		int day = prev_month_length + 1 - (startDayOfWeek - i);
		ui->laborSheet->setItem(i/7,i % 7, makeDateLabel(day) );
	}

	QTextCodec* codec = QTextCodec::codecForLocale();
	for(int i=startDayOfWeek ; i<startDayOfWeek+monthLength ; ++i)
	{
		int day = i - startDayOfWeek + 1;
		// Нужно вставить комбобоксы
        QComboBox* combo = new QComboBox();
		combo->insertItem(0, codec->toUnicode("-"));
		combo->insertItem(1, codec->toUnicode("--"));
		combo->setCurrentIndex(0);
		combo->setToolTip(codec->toUnicode("<html><head/><body><b>%1</b> число</body></html>").arg(day));
		_comboboxes.push_back(combo);
		ui->laborSheet->setCellWidget(i/7,i % 7, combo );
	}

	for(int i=startDayOfWeek+monthLength ; i<42 ; ++i)
	{
		// Нужно вставить лэйблы с числами после конца месяца
		int day = i - (startDayOfWeek+monthLength) + 1;

		ui->laborSheet->setItem(i/7,i % 7, makeDateLabel(day) );
	}
    ui->LabourGroupEdit->setEnabled(false);
    ui->employeeLaborSheetTable->setColumnWidth(0,0);

	// ! перемещено в конструктор
    //Connections
    //connect(ui->employeeLaborSheetTable,SIGNAL(currentCellChanged(int,int,int,int)),this, SLOT(showSelectedItem(int)));
}

/*! 
\param day в диапазоне [1..31]
\ returns указатель на QTableWidgetItem, который нужно будет потом удалить
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

	emit changeState(triggerState); // может быть, лучше сделать наоборот - чтобы переключение происходило по этому сигналу ???
}
void salarycountLaborSheet::updateInfo(QString name)
{
    if(this->objectName().compare(name) != 0)
		return;

    QList<LaborSheet>& labor_data = LaborSheet::getByPeriodId(_viewedPeriod->id());
	// > перенесено в конструктор (меняется единожды)
    //ui->BillingPeriod_dateEdit->setDate(_viewedPeriod->startDate());
    if(ui->employeeLaborSheetTable->rowCount() != labor_data.size())
	{
        ui->employeeLaborSheetTable->clearContents();
        int row = 0;
        for(int i = 0; i < labor_data.size(); ++i)
        {
            ui->employeeLaborSheetTable->insertRow(row);
            Employee employee(*(labor_data[i].employee()));
            ui->employeeLaborSheetTable->setItem(row,0,new QTableWidgetItem(QString(labor_data[i].id())));
            ui->employeeLaborSheetTable->setItem(row,1,new QTableWidgetItem(employee.fio()));
            ui->employeeLaborSheetTable->item(row,0)->setData(Qt::UserRole,labor_data[i].id());
			// TODO: добавить инфо по остальным столбцам (прочерки или реальные значения для закрытого месяца)
            ++row;
        }
        ui->employeeLaborSheetTable->setCurrentCell(0,1);
	}
}

void salarycountLaborSheet::showSelectedItem(int row)
{
    QTextCodec* codec = QTextCodec::codecForLocale();
    if(row >= 0)
    {
        int id = ui->employeeLaborSheetTable->item(row,0)->data(Qt::UserRole).toInt();
        LaborSheet labor_sheet(id,0,0,QList<Mark>());
        labor_sheet.fetch();
        QList<Mark>marks = labor_sheet.marks();
        int start = _viewedPeriod->startDate().dayOfWeek() - 1;
        if(labor_sheet.payForm() == PayForm::PER_MONTH)
        {
            //int row = 0;
        
            for(int i = start;i < marks.size() + start;++i){
                QComboBox* combo = (QComboBox*)ui->laborSheet->cellWidget(i/7,i%7);
                combo->insertItem(0,codec->toUnicode("Выходной"));
                combo->insertItem(1,codec->toUnicode("Рабочий"));
                combo->insertItem(2,codec->toUnicode("Отсутствовал"));
                if(marks[i - start].altered() == Mark::INVALID)
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
                QComboBox* combo = (QComboBox*)ui->DutyChartMarksEdit->cellWidget(i/7,i%7);
                for(int j = 0; j <= 12; ++j)
                {
                    combo->insertItem(j,QString(j));
                }
                if(marks[i - start].alteredCountHours() == Mark::INVALID) 
                    combo->setCurrentIndex(marks[i].countHours());
                else
                    combo->setCurrentIndex(marks[i].alteredCountHours());
            }
        }
    }
}
void salarycountLaborSheet::periodDateChanged(const QDate& date)
{
	BillingPeriod* bp = BillingPeriod::getByDate(date);
	if(bp)
	{
		delete this->_viewedPeriod;
		this->_viewedPeriod = bp;
		ui->ClosePeriod_button->setEnabled(this->_viewedPeriod->status() == BillingPeriod::OPEN);
		regenMarksCalendar();
	}
}
void salarycountLaborSheet::closePeriod()
{
	bool ok = BookKeeper::closeBillingPeriod(*this->_viewedPeriod);
	if(!ok)
	{
		// ERROR !!!
	}
	ui->ClosePeriod_button->setEnabled(this->_viewedPeriod->status() == BillingPeriod::OPEN);

	updateInfo(this->objectName());
}
void salarycountLaborSheet::editLaborSheet()
{
    switchMode(app_states::EDIT);
}