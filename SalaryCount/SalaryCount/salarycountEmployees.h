#ifndef SALARYCOUNTEMPLOYEES_H
#define SALARYCOUNTEMPLOYEES_H

#include "delegateStates.h"

class salarycountEmployees : public delegateStates
{
	Q_OBJECT

public:
	salarycountEmployees(Ui_SalaryCount *ui, QString name="");
	~salarycountEmployees();

private:
	
};

#endif // SALARYCOUNTEMPLOYEES_H
