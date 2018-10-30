#ifndef SALARYCOUNT_H
#define SALARYCOUNT_H

#include <QtWidgets/QMainWindow>
#include "employee.h"
#include "ui_salarycount.h"

class SalaryCount : public QMainWindow
{
    Q_OBJECT

public:
    SalaryCount(QWidget *parent = 0);
    ~SalaryCount();

private:
    Ui_SalaryCount ui;

private slots:
	void addDutyChart();//добавление нового графика
	void changePayForm(int index);

	void saveNewDutyChart();
	void cancelNewDutyChart();
};

#endif // SALARYCOUNT_H
