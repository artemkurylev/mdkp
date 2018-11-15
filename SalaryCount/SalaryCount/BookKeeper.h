
#pragma once

#include "BillingPeriod.h"
//#include "laborsheet.h"


/*! Форма оплаты труда. (помесячная/почасовая)
*/
enum PayForm
{
	PER_HOUR,
	PER_MONTH,
};

class LaborSheet;

/*! Бухгалтер. Инкапсулирует главные функции учёта труда
*/
class BookKeeper
{
public:
	/*! Вычислить зарплату за период по закрытому месячному табелю
	*/
	static bool calcAwardFor(LaborSheet & laborSheet);

	/*! Закрыть расчётный период, подвести его итоги (з/п и др.) и открыть следующий расчётный период
	*/
	static bool closeBillingPeriod(BillingPeriod & billingPeriod);


	static bool hireNewEmployee();

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
