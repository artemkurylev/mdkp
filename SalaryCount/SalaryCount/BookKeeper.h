
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
	/*! ��������� �������� �� ������ �� ��������� ��������� ������
	*/
	static bool calcAwardFor(LaborSheet & laborSheet);


private:
	friend class BookKeeperTest;

	/*! ���������� �������� �� ������ ��� ��������� ����� ������
	*/
	static float awardPerHoursForm(float hourSalary, int hours);

	/*! ���������� �������� �� ������ ��� ���������� ����� ������
	*/
	static float awardPerMonthForm(float monthSalary, int days, int workDays);

	
};

class BookKeeper
{
public:
	static bool calcSalary();
}
