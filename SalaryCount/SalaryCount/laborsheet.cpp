#include "laborsheet.h"

LaborSheet::LaborSheet()
    : DbRecord()
{
    _billingPeriod = NULL;
    _employee = NULL;
    _dutyChart = NULL;
    this->_award = 0;
}

LaborSheet::LaborSheet(int employeeId, int billingPeriodId)
    : DbRecord()
{
    _billingPeriod = NULL;
    _employee = NULL;
    _dutyChart = NULL;
    this->_employeeId = employeeId;
    this->_billingPeriodId = billingPeriodId;
    this->_award = 0;
}
LaborSheet::LaborSheet(const LaborSheet& laborsheet)
    : DbRecord()
{
    this->_id = laborsheet.id();
    this->_billingPeriodId = laborsheet.billingPeriodId();
    this->_dutyChartId = laborsheet.dutyChartId();
    this->_employeeId = laborsheet.employeeeId();
    this->_employee = NULL;
    this->_billingPeriod = NULL;
    this->_dutyChart = NULL;
    this->_grid = laborsheet.grid();
    this->_award = laborsheet.award();
}
LaborSheet::LaborSheet(int id, int billingPeriodId, int employeeId, QList<Mark> grid)
{
    this->_billingPeriodId = billingPeriodId;
    this->_employeeId = employeeId;
    this->_grid = grid;
    this->_id = id;
    _billingPeriod = NULL;
    _employee = NULL;
    _dutyChart = NULL;
    this->_award = 0;
}
LaborSheet::~LaborSheet()
{
	// free allocated record
	if(_employee != NULL)
	{
		delete _employee;
	}
	if(_billingPeriod != NULL)
	{
		delete _billingPeriod;
	}
	if(_dutyChart != NULL)
	{
		delete _dutyChart;
	}
}

QList<LaborSheetDescriptionLine> LaborSheet::description()
{
	LaborSheet def_lbsh(*this);
	def_lbsh.fillWithDefaults();

	// внимание: сейчас dl.base_value игнорируется при выводе в таблицу

	QList<LaborSheetDescriptionLine> l;
	//LaborSheetDescriptionLine dl = { QString::fromLocal8Bit("Сотрудник"), employee().name(), -1.0 };
	//l.push_back(dl);

	LaborSheetDescriptionLine dl = { QString::fromLocal8Bit("Форма оплаты"), QString::fromLocal8Bit((payForm() == PER_MONTH)? "Помесячная" : "Почасовая"), "", "", -1.0 };
	l.push_back(dl);

	dl.name = QString::fromLocal8Bit("Выплата");
	dl.default_value = QString::number(def_lbsh.award());
	if(billingPeriod()->status() == BillingPeriod::OPEN)
		dl.base_value = QString::fromLocal8Bit("(закройте месяц)");
	else
		dl.base_value = QString::number(this->award());
	dl.altered_value = dl.base_value;
	l.push_back(dl);

	int def_base_time = def_lbsh.countBaseTimeUnits(),
		cur_base_time = this->countBaseTimeUnits(),
		cur_alt_time =  this->countActualTimeUnits();

	if(payForm() == PER_HOUR)
	{
		dl.name = QString::fromLocal8Bit("Формула");
		dl.default_value = QString::fromLocal8Bit("Ставка * Часы");
		dl.base_value    = QString::fromLocal8Bit("");
		dl.altered_value = QString::fromLocal8Bit("%1 * %2")
			.arg(employee()->hireDirective()->salary())
			.arg(cur_alt_time);
		l.push_back(dl);

		dl.name = QString::fromLocal8Bit("Ставка");
		dl.default_value = QString::number(employee()->hireDirective()->salary());
		dl.base_value    = QString::fromLocal8Bit("");
		dl.altered_value = QString::fromLocal8Bit("---");
		l.push_back(dl);

		dl.name = QString::fromLocal8Bit("Часы");
		dl.default_value = QString::number(def_base_time);
		dl.base_value = QString::number(cur_base_time);
		dl.altered_value = QString::number(cur_alt_time);
		l.push_back(dl);
	}
	if(payForm() == PER_MONTH)
	{
		dl.name = QString::fromLocal8Bit("Формула");
		//dl.base_value = QString::fromLocal8Bit("Оклад * Дней_отработано / Рабочих_дней");
		dl.default_value = QString::fromLocal8Bit("Оклад * Дней_отработано / Рабочих_дней");
		dl.base_value    = QString::fromLocal8Bit("");
		dl.altered_value = QString::fromLocal8Bit("%1 * %2 / %3")
			.arg(QString::number(employee()->hireDirective()->salary()))
			.arg(cur_alt_time)
			.arg(def_base_time);
		l.push_back(dl);

		dl.name = QString::fromLocal8Bit("Оклад");
		dl.default_value = QString::number(employee()->hireDirective()->salary());
		dl.base_value    = QString::fromLocal8Bit("");
		dl.altered_value = QString::fromLocal8Bit("---");
		l.push_back(dl);

		dl.name = QString::fromLocal8Bit("Дни");
		dl.default_value = QString::number(def_base_time);
		dl.base_value = QString::number(cur_base_time);
		dl.altered_value = QString::number(cur_alt_time);
		l.push_back(dl);
	}

	dl.name = QString::fromLocal8Bit("Эффективность");
	dl.default_value = QString::fromLocal8Bit("100%");
	dl.base_value    = QString::fromLocal8Bit("");
	dl.altered_value = QString::fromLocal8Bit("%1%").arg(100*cur_alt_time / qMax(1 , def_base_time));
	l.push_back(dl);

	dl.name = QString::fromLocal8Bit("Пунктуальность");
	float /*summ2_base = 0,*/ summ2_altered = 0;
	// подсчитать отклонение
	{
		int marksN = this->grid().size();
		// s = sqrt( SUM( (x - x_0)^2 ) / N )
		for(int i=0 ; i<marksN ; ++i)
		{
			const Mark *mark_this, *mark_def;
			mark_this = &this->grid() [i];
			mark_def = &def_lbsh.grid() [i];
			// для почасовой вернуть часы;
			// для помесячной - 1, если отметка ненулевая, иначе 0.
			/* float diff_base = (payForm() == PER_HOUR)? 
				mark_this->countHours() - mark_def->countHours()
				:
				(mark_this->altered() == Mark::ATTENDS) - (mark_def->base() == Mark::ATTENDS); */
			float diff_altered = (payForm() == PER_HOUR)? 
				mark_this->alteredCountHours() - mark_def->countHours()
				:
				(mark_this->altered() == Mark::ATTENDS) - (mark_def->base() == Mark::ATTENDS);

			/*summ2_base	 +=	diff_base	 *	diff_base; */
			summ2_altered += diff_altered *	diff_altered;
		}
		/*summ2_base		= sqrt(summ2_base / marksN); */
		summ2_altered	= sqrt(summ2_altered / marksN);
	}
	dl.default_value = QString::fromLocal8Bit("100%");
	dl.base_value    = QString::fromLocal8Bit("");
	dl.altered_value = QString::fromLocal8Bit("%1% в среднем")
		.arg(QString::number(100*qMax(0.0F,qMin(1.0F,1.0F-summ2_altered/(float)def_base_time)),'f',1));
	l.push_back(dl);

	return l;
}

bool LaborSheet::fillWithDefaults()
{
	// Вычислить относительное смещение наложения графика на месяц
    this->dutyChart();
    this->billingPeriod();
    //this->billingPeriod()->fetch();
    const QDate buffer_date = this->_dutyChart->anchorDate();
    int count_diff_days = 0;
    count_diff_days = buffer_date.daysTo(this->_billingPeriod->startDate());
    int length = _dutyChart->length();
	while(count_diff_days < 0)
		count_diff_days += length;
    int bias = count_diff_days % length;
    int dutyChart_index = bias;
	
	this->_grid.clear();
	// Заполнить табель отметками по умолчанию
    int month_length = this->_billingPeriod->startDate().daysInMonth();
    for(int i = 0; i < month_length; ++i,dutyChart_index++)
    {
        if(dutyChart_index >= length)
            dutyChart_index = 0;
        Mark m(_dutyChart->grid()[dutyChart_index]);

		// записать ID в отметку!
		m.setDutyChartId( NULL );
		m.setLaborsheetId(this->_id);
		// сбросить изменённые данные
		m.resetAltered();

        this->_grid.push_back(m);
    }
	
	//// не обновляем табель в БД сразу (неизвестно - это update или insert)
    return true; // this->update();
}
void LaborSheet::commitChanges()
{
	// foreach(Mark& mark , _grid)
	for(int i=0 ; i<_grid.size() ; ++i)
	{
		_grid[i].commitChanges();
	}
}

Employee* LaborSheet::employee()
{
	if(_employee == NULL)
	{
		_employee = new Employee(_employeeId);
        _employee->fetch();
	}
	return _employee;
}
BillingPeriod* LaborSheet::billingPeriod()
{
	if(_billingPeriod == NULL)
	{
		_billingPeriod = new BillingPeriod(_billingPeriodId);
		_billingPeriod->fetch();
	}
	return _billingPeriod;
}
PayForm LaborSheet::payForm()
{
	//Employee* e = employee();
	//HireDirective* h = e->hireDirective();
	//PayForm p = h->payForm();
	//return p;
	return employee()->hireDirective()->payForm();
}
DutyChart* LaborSheet::dutyChart()
{
	if(_dutyChart == NULL)
	{
		_dutyChart = new DutyChart(_dutyChartId);
        _dutyChart->fetch();
	}
	return _dutyChart;
}

int LaborSheet::countBaseTimeUnits()
{
	int total = 0;
	enum PayForm pay_form;
	pay_form = payForm();

	foreach(Mark mark , this->grid())
	{
		// для почасовой вернуть часы;
		// для помесячной - 1, если отметка ненулевая, иначе 0.
		total += (pay_form == PER_HOUR)? 
			mark.countHours()
			:
			(mark.base() == Mark::ATTENDS);
	}

	return total;
}
int LaborSheet::countActualTimeUnits()
{
	int total = 0;
	enum PayForm pay_form;
	pay_form = payForm();

	foreach(Mark mark , this->grid())
	{
		// для почасовой вернуть часы;
		// для помесячной - 1, если отметка ненулевая, иначе 0.
		total += (pay_form == PER_HOUR)? 
			(mark.isAlteredCountHours() ? mark.alteredCountHours() : mark.countHours() )
			:
			(mark.isAltered() ? mark.altered() : mark.base() )
			;
	}

	return total;
}
bool LaborSheet::validate() const{
    return false;
}
int LaborSheet::insert()
{
	int insert_id = -1;
	if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

        query->prepare("INSERT INTO `labor_sheet` (billing_period_id,employee_id,dutychart_id, award) VALUES(:billing_period_id,:employee_id,:dutychart_id,:award)");
        query->bindValue(":billing_period_id",this->_billingPeriodId);
        query->bindValue(":employee_id",this->_employeeId);
        query->bindValue(":dutychart_id", this->_dutyChartId);
        query->bindValue(":award",this->_award);

        if(query->exec())
        {
            if(query->exec("SELECT LAST_INSERT_ID()") && query->next())
			{
				this->_id = query->value(0).toInt();
                insert_id = this->_id;
			}
			// создать все отметки в БД
            for(int i = 0; i < this->_grid.length(); ++i)
            {
				// записать ID в отметку!
				this->_grid[i].setLaborsheetId(this->_id);

                if(this->_grid[i].insert()== - 1)
                {
                    //Ошибка!!
                }
            }
        }
        else
        {
            //Ошибка!
            QString s = query->lastError().text();
            s+="as";
        }
        delete query;
    }
    else
	{
    }
	return insert_id;
}
bool LaborSheet::update() const
{
	bool success = false;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        query->prepare("UPDATE `labor_sheet` SET billing_period_id = :billing_period_id , employee_id = :employee_id, dutychart_id = :dutychart_id, award = :award WHERE `id` =:id");
        query->bindValue(":billing_period_id",this->_billingPeriodId);
        query->bindValue(":employee_id",this->_employeeId);
        query->bindValue(":dutychart_id",this->_dutyChartId);
        query->bindValue(":award",this->_award);
        query->bindValue(":id",this->id());
        if(query->exec())
        {
            success = true;
            for(int i = 0; i < _grid.size(); ++i)
            {
                if(!_grid[i].update())
                {
                    //Ошибка!!!
			        success = false;
                }
            }
        }
        else
        {
        }
        delete query;
    }
    return success;
}
bool LaborSheet::createDbTable()
{
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        if(query->exec("CREATE TABLE IF NOT EXISTS `labor_sheet` (`id` INT(11) NOT NULL AUTO_INCREMENT, `billing_period_id` INT(11), `employee_id` INT(11),`dutychart_id` INT(11), `award` FLOAT NULL, PRIMARY KEY(`id`))"))
            return true;
        else
        {
            QString s = query->lastError().text();
            s+="as";
            return false;
        }
        delete query;
    }
    else
    {
        return false;
    }
}    
QMap <int, int> LaborSheet::getAll()
{
    QMap <int, int> result;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        if(query->exec("SELECT id,employee_id FROM `labor_sheet`"))
        {
            while(query->next())
            {
                result.insert(query->value(0).toInt(),query->value(1).toInt());
            }
        }
    }
    return result;
}
bool LaborSheet::fetch()
{
	bool success = false;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

        query->prepare("SELECT * FROM `labor_sheet` WHERE `id` = :id");
        int id = this->id();
        query->bindValue(":id",id);
        if(query->exec())
        {
            if(query->next())
            {
				// получить ID сотрудника
                this->_employeeId = query->value(2).toInt();

				// получить ID периода
                this->_billingPeriodId = query->value(1).toInt();
				
				// получить ID графика
                this->_dutyChartId = query->value(3).toInt();

				// получить выплату
                this->_award = query->value(4).toFloat();

     //           QSqlQuery query_b = *(DbManager::manager().makeQuery());
     //           query_b.prepare("SELECT * FROM `billing_period` WHERE `id` = :billing_period_id");
     //           query_b.bindValue(":billing_period_id",query->value(1).toInt());
     //           if(query->exec() && query->next())
     //           {
					//this->_billingPeriodId = 
     //               BillingPeriod* period = new BillingPeriod(query->value(1).toDate(),(BillingPeriod::Status)query->value(2).toInt());
     //               this->_billingPeriod = period;
     //           }
     //           if(query->exec() && query->next())
     //           {
     //               DutyChart* dutyChart = new DutyChart(query->value(3).toInt());
     //               this->_dutyChart = dutyChart;
     //			  }

                QSqlQuery query_m = *(DbManager::manager().makeQuery());
                query_m.prepare("SELECT * FROM `mark` WHERE `laborsheet_id` = :id");
                query_m.bindValue(":id", id);
                if(query_m.exec())
                {
                    while(query_m.next())
                    {
                        Mark m(query_m.value(1).toInt(),
							query_m.value(2).toInt(),
							query_m.value(3).toInt(),
							query_m.value(4).toInt(),
							query_m.value(5).toInt(),
							query_m.value(6).toInt()
							);
                        int mark_id = query_m.value(0).toInt();
                        m.setId(mark_id);
                        _grid.append(m);
                    }
					success = true;
                }
            }
        }
        else
        {
            QString s = query->lastError().text();
            s+="as";
        }
        delete query;
    }
    return success;
}
bool LaborSheet::fetch(int employeeid,int periodId)
{
    bool success = false;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

        query->prepare("SELECT * FROM `labor_sheet` WHERE `billing_period_id` = :billing_period_id AND `employee_id` = :employee_id");
        query->bindValue(":billing_period_id",periodId);
        query->bindValue(":employee_id",employeeid);
        if(query->exec())
        {
            if(query->next())
            {
                //Получить id таблея
                this->_id = query->value(0).toInt();
				// получить ID сотрудника
                this->_employeeId = query->value(2).toInt();

				// получить ID периода
                this->_billingPeriodId = query->value(1).toInt();
				
				// получить ID графика
                this->_dutyChartId = query->value(3).toInt();

				// получить выплату
                this->_award = query->value(4).toFloat();

     //           QSqlQuery query_b = *(DbManager::manager().makeQuery());
     //           query_b.prepare("SELECT * FROM `billing_period` WHERE `id` = :billing_period_id");
     //           query_b.bindValue(":billing_period_id",query->value(1).toInt());
     //           if(query->exec() && query->next())
     //           {
					//this->_billingPeriodId = 
     //               BillingPeriod* period = new BillingPeriod(query->value(1).toDate(),(BillingPeriod::Status)query->value(2).toInt());
     //               this->_billingPeriod = period;
     //           }
     //           if(query->exec() && query->next())
     //           {
     //               DutyChart* dutyChart = new DutyChart(query->value(3).toInt());
     //               this->_dutyChart = dutyChart;
     //			  }

                QSqlQuery query_m = *(DbManager::manager().makeQuery());
                query_m.prepare("SELECT * FROM `mark` WHERE `laborsheet_id` = :id");
                int id = this->_id;
                query_m.bindValue(":id", id);
                if(query_m.exec())
                {
                    while(query_m.next())
                    {
                        Mark m(query_m.value(1).toInt(),
							query_m.value(2).toInt(),
							query_m.value(3).toInt(),
							query_m.value(4).toInt(),
							query_m.value(5).toInt(),
							query_m.value(6).toInt()
							);
                        int mark_id = query_m.value(0).toInt();
                        m.setId(mark_id);
                        _grid.append(m);
                    }
					success = true;
                }
            }
        }
        else
        {
            QString s = query->lastError().text();
            s+="as";
        }
        delete query;
    }
    return success;
}
long LaborSheet::countEntries()
{
    int counter = 0;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

        query->prepare("SELECT COUNT(*) FROM `labor_sheet`");
        if(query->exec())
        {
            if(query->next())
                counter = query->value(0).toInt();
        }
        delete query;
    }
    return counter;
}
QList<LaborSheet> LaborSheet::getByPeriodId(int id)
{
    QList<LaborSheet> labor_list;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();

        query->prepare("SELECT * FROM `labor_sheet` WHERE `billing_period_id` = :id");
        query->bindValue(":id",id);
        if(query->exec())
        {
            while(query->next())
            {
				// необходимо проверить работоспособность
				LaborSheet labor;
				int labor_id = query->value(0).toInt();
				labor._id = labor_id;
				labor.fetch();

				// ! этот блок можно заменить на LaborSheet(id) c автоматической выборкой по id (проверить действия метода LaborSheet.fetch())
      ////          QList <Mark> grid;
      ////          int labor_id = query->value(0).toInt();
      ////          QSqlQuery query_m = *(DbManager::manager().makeQuery());
      ////          query_m.prepare("SELECT * from `mark` WHERE laborsheet_id = :id");
      ////          query_m.bindValue(":id",labor_id);
      ////          if(query_m.exec())
      ////          {
      ////              while(query_m.next())
      ////              {
      ////                  Mark m(query_m.value(1).toInt(),query_m.value(2).toInt(),query_m.value(3).toInt(),query_m.value(4).toInt(),query_m.value(5).toInt(),query_m.value(6).toInt());
      ////                  int x =query_m.value(0).toInt();
						////m.setId(x);
      ////                  grid.append(m);
      ////              }
      ////          }
      ////          LaborSheet labor(query->value(0).toInt(),query->value(1).toInt(),query->value(2).toInt(),grid);
                labor_list.append(labor);
            }
        }
    }
    return labor_list;
}