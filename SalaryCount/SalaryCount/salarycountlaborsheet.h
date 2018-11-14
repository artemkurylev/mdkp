#ifndef SALARYCOUNTLABORSHEET_H
#define SALARYCOUNTLABORSHEET_H

#include "delegateStates.h"
#include "laborsheet.h"
#include<qtablewidget.h>
class salarycountLaborSheet : public delegateStates
{
    Q_OBJECT

public:
	salarycountLaborSheet(Ui_SalaryCount *ui, QString name="");
    ~salarycountLaborSheet();

private:

    Ui_SalaryCount *ui; // не самый при€тный способ, зато все видно из коробки
	void showAllLabors();
};

#endif // SALARYCOUNTLABORSHEET_H
