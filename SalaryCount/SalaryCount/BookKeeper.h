#pragma once

#include "laborsheet.h"

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

	/*! Подсчитать зарплату за период для почасовой формы оплаты
	*/
	static float awardPerHoursForm(float hourSalary, int hours);

	/*! Подсчитать зарплату за период для помесячной формы оплаты
	*/
	static float awardPerMonthForm(float monthSalary, int days, int workDays);


};
