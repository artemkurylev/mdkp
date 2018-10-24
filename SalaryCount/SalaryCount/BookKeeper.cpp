#include "BookKeeper.h"


bool BookKeeper::calcSalary(const LaborSheet & laborSheet)
{
	return false;
}

static float BookKeeper::calcPerHoursSalary(float hourSalary, int hours)
{
	return hourSalary * hours;
}

static float BookKeeper::calcPerMonthSalary(float monthSalary, int days, int workDays)
{
	return monthSalary * days / workDays;
}

