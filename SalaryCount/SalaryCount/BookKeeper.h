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

private:

	/*! ���������� �������� �� ������ ��� ��������� ����� ������
	*/
	static float calcPerHoursSalary(float hourSalary, int hours);

	/*! ���������� �������� �� ������ ��� ���������� ����� ������
	*/
	static float calcPerMonthSalary(float monthSalary, int days, int workDays);


};
