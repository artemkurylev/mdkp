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
	static bool calcSalary(const LaborSheet & laborSheet);

	/*! Заполнить табель за период отметками по умолчанию
	*/
	static bool fillLaborsheetWithDefaults(LaborSheet & laborSheet);

private:

	/*! Подсчитать плановое рабочее время за период
	*/
	static int countDefaultLaborTimeUnits(const LaborSheet & laborSheet);

	/*! Подсчитать отработанное время за период
	*/
	static int countActualLaborTimeUnits (const LaborSheet & laborSheet);

	/*! Подсчитать зарплату за период для почасовой формы оплаты
	*/
	static float calcPerHoursSalary(float hourSalary, int hours);

	/*! Подсчитать зарплату за период для помесячной формы оплаты
	*/
	static float calcPerMonthSalary(float monthSalary, int days, int workDays);


};
