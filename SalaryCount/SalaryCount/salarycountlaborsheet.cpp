#include "salarycountlaborsheet.h"

QTableWidgetItem* makeDateLabel(int day);


salarycountLaborSheet::salarycountLaborSheet(Ui_SalaryCount *ui, QString name)
{
	this->setObjectName(name);
	this->ui = ui;//�� ����� �������� ������

	BillingPeriod* _viewedPeriod = BillingPeriod::getCurrentPeriod();
	ui->ClosePeriod_button->setEnabled(true);
	connect(ui->BillingPeriod_dateEdit,SIGNAL(dateChanged(const QDate&)), this,SLOT(periodDateChanged(const QDate&))); // �������� ���� �������� �������
	connect(ui->ClosePeriod_button,SIGNAL(dateChanged(const QDate&)), this,SLOT(periodDateChanged(const QDate&))); // �������� ���� �������� �������

	_startDayOfWeek=0 ; _monthLength=0; // ����� ����� �������������??
	regenMarksCalendar();	// �������� ������ ��� �������

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
	
	// ������� ������� � ��������� ��������
	ui->laborSheet->clearContents();
	_comboboxes.clear();

	// �������� ������� ������...

	for(int i=0 ; i<startDayOfWeek ; ++i)
	{
		// ����� �������� ������ � ������� �� ������ ������
		int day = prev_month_length + 1 - (this->_startDayOfWeek - i);
		ui->laborSheet->setItem(i/7,i % 7, makeDateLabel(day) );
	}

	QTextCodec* codec = QTextCodec::codecForLocale();
	for(int i=startDayOfWeek ; i<startDayOfWeek+monthLength ; ++i)
	{
		int day = i - startDayOfWeek + 1;
		// ����� �������� ����������
        QComboBox* combo = new QComboBox();
		combo->insertItem(0, codec->toUnicode("-"));
		combo->insertItem(1, codec->toUnicode("--"));
		combo->setCurrentIndex(0);
		combo->setToolTip(codec->toUnicode("<html><head/><body><b>%1</b> �����</body></html>").arg(day));
		_comboboxes.push_back(combo);
		ui->laborSheet->setCellWidget(i/7,i % 7, combo );
	}


	for(int i=startDayOfWeek+monthLength ; i<42 ; ++i)
	{
		// ����� �������� ������ � ������� ����� ����� ������
		int day = i - startDayOfWeek+monthLength + 1;
		ui->laborSheet->setItem(i/7,i % 7, makeDateLabel(day) );
	}
	
	this->_startDayOfWeek = startDayOfWeek;
	this->_monthLength = monthLength;
}

/*! 
\param day � ��������� [1..31]
\ returns ��������� �� QTableWidgetItem, ������� ����� ����� ����� �������
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

	ui->dutyChartEdit->setEnabled(triggerState);
	ui->dutyChartBox->setEnabled(!triggerState);

	emit changeState(triggerState); // ����� ����, ����� ������� �������� - ����� ������������ ����������� �� ����� ������� ???
}
void salarycountLaborSheet::updateInfo(QString name)
{
    if(!this->objectName().compare(name))
		return;

    QList<LaborSheet>& labor_data = LaborSheet::getByPeriodId(_viewedPeriod->id());
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
			// TODO: �������� ���� �� ��������� �������� (�������� ��� �������� �������� ��� ��������� ������)
            ++row;
        }
        ui->employeeLaborSheetTable->setCurrentCell(0,1);
	}
}

void salarycountLaborSheet::showLabor()
{
    int row = ui->employeeLaborSheetTable->currentIndex().row();
    int id = ui->employeeLaborSheetTable->item(row,0)->text().toInt();
    LaborSheet labor_sheet(id);
    labor_sheet.fetch();
    QList<Mark>marks = labor_sheet.marks();
    if(labor_sheet.payForm() == PayForm::PER_MONTH)
    {
        //int row = 0;
        for(int i = 0; i<marks.size();++i)
		{
			// TODO: ���������� �� ��������� � _comboboxes
            QComboBox* combo = (QComboBox*)ui->DutyChartMarksEdit->cellWidget(i/7,i%7);
            combo->insertItem(0,"��������");
            combo->insertItem(1,"�������");
            combo->insertItem(2,"������������");
            if(marks[i].altered() == Mark::INVALID)
            {
                switch(marks[i].base())
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
                switch(marks[i].altered())
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
        for(int i = 0;i <marks.size();++i)
        {
            QComboBox* combo = (QComboBox*)ui->DutyChartMarksEdit->cellWidget(i/7,i%7);
            for(int j = 0; j <= 12; ++j)
            {
                combo->insertItem(j,QString(j));
            }
            if(marks[i].alteredCountHours() == Mark::INVALID) 
                combo->setCurrentIndex(marks[i].countHours());
            else
                combo->setCurrentIndex(marks[i].alteredCountHours());
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
