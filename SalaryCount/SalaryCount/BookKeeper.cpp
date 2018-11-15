#include "BookKeeper.h"


bool BookKeeper::calcAwardFor(LaborSheet & laborSheet)
{


	return false;
}

bool BookKeeper::closeBillingPeriod(BillingPeriod & billingPeriod)
{
	int bp_status = billingPeriod.status();
	BillingPeriod & next_period = *billingPeriod.nextPeriod();
	if( bp_status != BillingPeriod::OPEN &&		// НАЙДЕН способ обрщения к чужим enum`ам !
		bp_status != BillingPeriod::MODIFIED &&
		next_period.status() != BillingPeriod::NOT_OPENED )
	{
		// preconditions error
		return false;
	}

	billingPeriod.close();
	billingPeriod.update();

	// расчитать з/п
	// Для каждого табеля в текущем периоде...
	// ... Вычислить зарплату за период по закрытому месячному табелю

	next_period.open();
	next_period.update();
	
	return true;
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

