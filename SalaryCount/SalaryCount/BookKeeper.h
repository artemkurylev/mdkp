
#pragma once

#include "laborsheet.h"
#include "BillingPeriod.h"
/*! Форма оплаты труда. (помесячная/почасовая)
*/
enum PayForm
{
	PER_HOUR,
	PER_MONTH,
};



/*! Бухгалтер. Инкапсулирует главные функции учёта труда
*/
class BookKeeper
{
public:
	/*! Вычислить зарплату за период по закрытому месячному табелю
	*/
	static bool calcAwardFor(LaborSheet & laborSheet);

	static bool openBillingPeriod(BillingPeriod & billingPeriod);

private:
	friend class BookKeeperTest;

	/*! Подсчитать зарплату за период для почасовой формы оплаты
	*/
	static float awardPerHoursForm(float hourSalary, int hours);

	/*! Подсчитать зарплату за период для помесячной формы оплаты
	*/
	static float awardPerMonthForm(float monthSalary, int days, int workDays);

	
};

class BookKeeper
{
public:
	static bool calcSalary();
}
