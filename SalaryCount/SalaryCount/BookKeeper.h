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
	
	/*! ��������� ������ �� ������ ��������� �� ���������
	TODO: ������� ������� ������ LaborSheet
	*/
	static bool fillLaborsheetWithDefaults(LaborSheet & laborSheet);

private:

	/*! ���������� �������� ������� ����� �� ������
	TODO: ������� ������� ������ LaborSheet
	*/
	static int countDefaultLaborTimeUnits(const LaborSheet & laborSheet);

	/*! ���������� ������������ ����� �� ������
	TODO: ������� ������� ������ LaborSheet
	*/
	static int countActualLaborTimeUnits (const LaborSheet & laborSheet);

	/*! ���������� �������� �� ������ ��� ��������� ����� ������
	*/
	static float calcPerHoursSalary(float hourSalary, int hours);

	/*! ���������� �������� �� ������ ��� ���������� ����� ������
	*/
	static float calcPerMonthSalary(float monthSalary, int days, int workDays);


};
