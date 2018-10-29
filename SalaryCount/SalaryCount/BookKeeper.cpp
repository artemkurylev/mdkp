#include "BookKeeper.h"


bool BookKeeper::calcAwardFor(LaborSheet & laborSheet)
{


	return false;
}
bool openBillingPeriod(BillingPeriod & billingPeriod)
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

