
#pragma once

#include "laborsheet.h"
#include "BillingPeriod.h"
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

	static bool openBillingPeriod(BillingPeriod & billingPeriod);

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
