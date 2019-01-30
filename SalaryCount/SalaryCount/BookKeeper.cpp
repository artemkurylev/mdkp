
#include "BookKeeper.h"


bool BookKeeper::calcAwardFor(LaborSheet & laborSheet)
{


	return false;
}

bool BookKeeper::closeBillingPeriod(BillingPeriod & billingPeriod)
{
	int bp_status = billingPeriod.status();
	BillingPeriod & next_period = *billingPeriod.nextPeriod();
	if( bp_status != BillingPeriod::OPEN &&		// ������ ������ �������� � ����� enum`�� !
		bp_status != BillingPeriod::MODIFIED &&
		next_period.status() != BillingPeriod::NOT_OPENED )
	{
		// preconditions error
		return false;
	}

	billingPeriod.close();
	billingPeriod.update();

	// ��������� �/�
	// ��� ������� ������ � ������� �������...
	// ... ��������� �������� �� ������ �� ��������� ��������� ������

	next_period.open();
	next_period.update();

	// ����������� ������
	// ��� ������� ����������, ���� ������ �� ������ �� ����� ������ �������� ������� ...
	// ... ������� ������ � ������� �������
	//	   ��������� ������ ������, ������ �� ������ ����������
	//	   ��������� ������ ��������� �� ���������.

	
	return true;
}

/*static*/ bool hireNewEmployee()
{
	return false;
}

float BookKeeper::awardPerHoursForm(float hourSalary, int hours)
{
	
}

float BookKeeper::awardPerMonthForm(float monthSalary, int days, int workDays)
{

	// TODO: handle negative params & zero workDays
	return monthSalary * days / workDays;
}


bool BookKeeper::calcSalary() 
{
	return false;
}
