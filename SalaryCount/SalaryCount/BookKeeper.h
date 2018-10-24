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
	*/
	static int countDefaultLaborTimeUnits(const LaborSheet & laborSheet);

	/*! Подсчитать отработанное время за период
	*/
	static int countActualLaborTimeUnits (const LaborSheet & laborSheet);

	static float calcPerHoursSalary(float basic_salary, int hours);
	static float calcPerMonthSalary(float basic_salary, int days, int workDays);


};
