#ifndef SALARYCOUNTLABORSHEET_H
#define SALARYCOUNTLABORSHEET_H

#include "delegateStates.h"
#include "laborsheet.h"
#include"BillingPeriod.h"
#include<qtablewidget.h>
class salarycountLaborSheet : public delegateStates
{
    Q_OBJECT

public:
	salarycountLaborSheet(Ui_SalaryCount *ui, QString name="");
    ~salarycountLaborSheet();

public slots:
	void updateInfo(QString name);

private:

    Ui_SalaryCount *ui; // не самый приятный способ, зато все видно из коробки
    void switchMode(app_states state);
	// текущий отображаемый расчётный период
	BillingPeriod* _viewedPeriod;

private slots:
    void showLabor();
	void periodDateChanged(QDate date); // TODO: connect to dateEdit
};

#endif // SALARYCOUNTLABORSHEET_H
