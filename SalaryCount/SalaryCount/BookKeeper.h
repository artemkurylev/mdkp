#pragma once

#include "laborsheet.h"

/*! ����� ������ �����. (����������/���������)
*/
enum PayForm
{
	PER_HOUR,
	PER_MONTH,
};



/*! ���������. ������������� ������� ������� ����� �����
*/
class BookKeeper
{
public:
	static bool calcSalary(const LaborSheet & laborSheet);


	static bool fillLaborsheetWithDefaults(LaborSheet & laborSheet);

private:

	/*! ���������� �������� ������� ����� �� ������
	*/
	static int countDefaultLaborTimeUnits(const LaborSheet & laborSheet);

	/*! ���������� ������������ ����� �� ������
	*/
	static int countActualLaborTimeUnits (const LaborSheet & laborSheet);

	static float calcPerHoursSalary(float basic_salary, int hours);
	static float calcPerMonthSalary(float basic_salary, int days, int workDays);


};
