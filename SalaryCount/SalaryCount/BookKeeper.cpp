
#include "BookKeeper.h"

#include "employee.h"
#include "laborsheet.h"


bool BookKeeper::calcAwardFor(LaborSheet & laborSheet)
{


	return false;
}

bool BookKeeper::closeBillingPeriod(BillingPeriod & billingPeriod)
{
	int bp_status = billingPeriod.status();
	BillingPeriod & next_period = *billingPeriod.nextPeriod();
	if( bp_status != BillingPeriod::OPEN &&		// ������ ������ �������� � ����� enum`�� !
		//bp_status != BillingPeriod::MODIFIED &&
		next_period.status() != BillingPeriod::NOT_OPENED )
	{
		// preconditions error
		return false;
	}

	billingPeriod.close();
	billingPeriod.update();

	// ��������� �/�
	// ��� ������� ������ � ������� �������...
	// ... [ ��������� ��������� ��������� �� ������� ��������� ������� ]
	// ... ��������� �������� �� ������ �� ��������� ��������� ������
	QList<LaborSheet> lbrsh_list = LaborSheet::getByPeriodId(billingPeriod.id());
	foreach(LaborSheet lbrsh, lbrsh_list)
	{
		// [...]
		BookKeeper::calcAwardFor(lbrsh);
	}

	next_period.open();
	next_period.update();

	// ����������� ������ ��� ����� ��������� �������
	// ��� ������� ����������, ���� ������ �� ������ �� ����� ������ �������� ������� ...
	// ... "�������������" ������ � ������������ � ������
	//     ������� ������ � ������� �������
	//	   ��������� ������ ������, ������� ��� ����������
	//	   ��������� ������ ��������� �� ���������.

	QList<int> employees = Employee::getAll().keys();
	foreach(int id, employees)
	{
		Employee emp(id);
		if(emp.hireDate() <= next_period.startDate()) // ������ ��� �������� �����������
		{
			// "�������������" ������
			if(emp.applyDutyChartChange(next_period.startDate()))
			{
				// ��������� ���������
				emp.update();
			}

			// ������� ������ � ������� �������
			LaborSheet lbrsh( emp.id(), next_period.id() );
			// ��������� ������ ������, ������� ��� ����������
			lbrsh.setDutyChartId( emp.currentDutyChartID() );
			// ��������� ������ ��������� �� ���������
			// � ��������� � ��
			lbrsh.fillWithDefaults();
		}

	}
	
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
