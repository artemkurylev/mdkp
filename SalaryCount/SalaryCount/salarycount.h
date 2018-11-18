#ifndef SALARYCOUNT_H
#define SALARYCOUNT_H

#include <QtWidgets/QMainWindow>

#include <qmessagebox.h>
#include "employee.h"
#include"laborsheet.h"
#include "ui_salarycount.h"
#include "BookKeeper.h"
#include "mark.h"
#include "dutychart.h"

#include "salarycountDutyChart.h"
#include "salarycountEmployees.h"
#include "salarycountlaborsheet.h"
#include "salarycountdirectives.h"
class SalaryCount : public QMainWindow
{
    Q_OBJECT

private:
	QAction* currentAction;

public:
    SalaryCount(QWidget *parent = 0);
    ~SalaryCount();

private:

    Ui_SalaryCount ui;

	salarycountDutyChart* dutyChart;
	salarycountEmployees* employees;
    salarycountLaborSheet* laborSheet;
    salarycountDirectives* directives;
	bool editState;

private:
	bool isEditable();
	void showStackedItem(QString namePage);

	//конструкторы
	void initialDBManager();

signals:
	void cancelChanges();
	void saveChanges();
	void showPage(QString name);

private slots:

	void rememberState(bool state);

	//переходы по страницам приложения
	void showPage(QAction* actionEmited);
};
#endif // SALARYCOUNT_H
