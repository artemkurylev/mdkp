#include "BookKeeper.h"


 bool BookKeeper::calcSalary(const LaborSheet & laborSheet)
{
	return false;
}

float BookKeeper::calcPerHoursSalary(float hourSalary, int hours)
{
	return hourSalary * hours;
}
 float BookKeeper::calcPerMonthSalary(float monthSalary, int days, int workDays)
{
	return monthSalary * days / workDays;
}

