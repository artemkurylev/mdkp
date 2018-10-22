#pragma once

#include "laborsheet.h"

/*! ‘орма оплаты труда. (помес€чна€/почасова€)
*/
enum PayForm
{
	PER_HOUR,
	PER_MONTH,
};



/*! Ѕухгалтер. »нкапсулирует главные функции учЄта труда
*/
class BookKeeper
{
public:
	static bool calcSalary(const LaborSheet & laborSheet);


	bool fillLaborsheetWithDefaults(LaborSheet & laborSheet);

private:


};
