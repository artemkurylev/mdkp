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
	static float calcBaseAwardFor(LaborSheet & laborSheet);

	/*! ������� ��������� ������, �������� ��� ����� (�/� � ��.) � ������� ��������� ��������� ������
	*/
	static bool closeBillingPeriod(BillingPeriod & billingPeriod);

	/*! ������� ���������� �� ������ � ���������� ������ ������, ��������� �������, ��������� �������. */
	static bool hireNewEmployee();

private:

	/*! ���������� �������� �� ������ ��� ��������� ����� ������
	*/
	static float awardPerHoursForm(float hourSalary, int hours);

	/*! ���������� �������� �� ������ ��� ���������� ����� ������
	*/
	static float awardPerMonthForm(float monthSalary, int days, int workDays);

	
};
