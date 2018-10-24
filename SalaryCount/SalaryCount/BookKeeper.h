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

private:

	/*! Подсчитать плановое рабочее время за период
	TODO: сделать методом класса LaborSheet
	*/
	static int countDefaultLaborTimeUnits(const LaborSheet & laborSheet);

	/*! Подсчитать отработанное время за период
	TODO: сделать методом класса LaborSheet
	*/
	static int countActualLaborTimeUnits (const LaborSheet & laborSheet);

	/*! Подсчитать зарплату за период для почасовой формы оплаты
	*/
	static float calcPerHoursSalary(float hourSalary, int hours);

	/*! Подсчитать зарплату за период для помесячной формы оплаты
	*/
	static float calcPerMonthSalary(float monthSalary, int days, int workDays);


};
