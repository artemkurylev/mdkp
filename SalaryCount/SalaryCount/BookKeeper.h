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


	bool fillLaborsheetWithDefaults(LaborSheet & laborSheet);

private:


};
