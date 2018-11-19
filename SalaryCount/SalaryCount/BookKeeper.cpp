#include "BookKeeper.h"

#include "employee.h"
#include "laborsheet.h"


bool BookKeeper::calcAwardFor(LaborSheet & laborSheet)
{


	return false;
}

bool BookKeeper::closeBillingPeriod(BillingPeriod & billingPeriod)
{
	int bp_status = billingPeriod.status();
	BillingPeriod & next_period = *billingPeriod.nextPeriod();
	if( bp_status != BillingPeriod::OPEN &&		// НАЙДЕН способ обрщения к чужим enum`ам !
		//bp_status != BillingPeriod::MODIFIED &&
		next_period.status() != BillingPeriod::NOT_OPENED )
	{
		// preconditions error
		return false;
	}

	billingPeriod.close();
	billingPeriod.update();

	// расчитать з/п
	// Для каждого табеля в текущем периоде...
	// ... [ Вычислить суммарную коррекцию за прошлые изменённые периоды ]
	// ... Вычислить зарплату за период по закрытому месячному табелю
	QList<LaborSheet> lbrsh_list = LaborSheet::getByPeriodId(billingPeriod.id());
	foreach(LaborSheet lbrsh, lbrsh_list)
	{
		// [...]
		BookKeeper::calcAwardFor(lbrsh);
	}

	next_period.open();
	next_period.update();

	// подготовить табеля для вновь открытого периода
	// Для каждого сотрудника, если принят на работу не позже начала текущего периода ...
	// ... "проапгрейдить" график в соответствии с планом
	//     создать табель в текущем периоде
	//	   назначить табелю график, текущий для сотрудника
	//	   заполнить табель отметками по умолчанию.

	QList<int> employees = Employee::getAll().keys();
	foreach(int id, employees)
	{
		Employee emp(id);
        emp.fetch();
		if(emp.hireDate() <= next_period.startDate()) // только для принятых сотрудников
		{
			// "проапгрейдить" график
			if(emp.applyDutyChartChange(next_period.startDate()))
			{
				// сохранить изменённое
				emp.update();
			}

			// создать табель в текущем периоде
			LaborSheet lbrsh( emp.id(), next_period.id() );
			// назначить табелю график, текущий для сотрудника
			lbrsh.setDutyChartId( emp.currentDutyChartID() );
			// заполнить табель отметками по умолчанию
			// И сохранить в БД
			lbrsh.fillWithDefaults();
            lbrsh.insert();
		}

	}
	
	return true;
}

/*static*/ bool hireNewEmployee()
{
	return false;
}

float BookKeeper::awardPerHoursForm(float hourSalary, int hours)
{
	return hourSalary * hours;
}

float BookKeeper::awardPerMonthForm(float monthSalary, int days, int workDays)

{
	// TODO: handle negative params & zero workDays
	return monthSalary * days / workDays;
}

