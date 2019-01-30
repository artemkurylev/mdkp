
#pragma once

#include "BillingPeriod.h"
//#include "laborsheet.h"


/*! ����� ������ �����. (����������/���������)
*/
enum PayForm
{
	PER_HOUR,
	PER_MONTH,
};

class LaborSheet;

/*! ���������. ������������� ������� ������� ����� �����
*/
class BookKeeper
{
public:
	/*! ��������� �������� �� ������ �� ��������� ��������� ������
	*/
	static bool calcAwardFor(LaborSheet & laborSheet);

	/*! ������� ��������� ������, �������� ��� ����� (�/� � ��.) � ������� ��������� ��������� ������
	*/
	static bool closeBillingPeriod(BillingPeriod & billingPeriod);


	static bool hireNewEmployee();

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
