#include "BookKeeper.h"

#include "employee.h"
#include "laborsheet.h"


float BookKeeper::calcBaseAwardFor(LaborSheet & laborSheet)
{
	float award;

    Employee* emp =  laborSheet.employee();
    HireDirective* hiredir = emp->hireDirective();
	int time = laborSheet.countBaseTimeUnits();
	float time_price = hiredir->salary();
	PayForm pay_form = hiredir->payForm();

	if(pay_form == PER_HOUR)
	{
		award = awardPerHoursForm(time_price, time);
	}
	else
	{
		LaborSheet defaultLaborSheet(laborSheet);
		defaultLaborSheet.fillWithDefaults();
		int default_days = defaultLaborSheet.countBaseTimeUnits();
		award = awardPerMonthForm(time_price, time, default_days);
	}

	return award;
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
		lbrsh.commitChanges();
		float award = BookKeeper::calcBaseAwardFor(lbrsh);
		lbrsh.setAward(award);
		lbrsh.update();
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
        emp.fetch();
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
            lbrsh.insert();
		}

	}
	
	return true;
}

/*static*/ bool BookKeeper::hireNewEmployee()
{
	return false;
}

float BookKeeper::awardPerHoursForm(float hourSalary, int hours)
{
	return hourSalary * hours;
}

float BookKeeper::awardPerMonthForm(float monthSalary, int days, int workDays)

{
	// TODO: handle negative params & zero workDays
	return monthSalary * days / workDays;
}

