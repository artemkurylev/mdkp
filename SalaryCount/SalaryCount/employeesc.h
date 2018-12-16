#ifndef EMPLOYEESC_H
#define EMPLOYEESC_H

#include <QtWidgets/QMainWindow>
#include <qmessagebox.h>
#include "delegateStates.h"
#include "employee.h"
#include "laborsheet.h"
#include "ui_employeesc.h"

#define MAX_WORKING_COUNT_HOURS 12

class EmployeeSC : public QMainWindow//, public delegateStates

class EmployeeSC : public QMainWindow // , virtual public delegateStates
{
    Q_OBJECT

public:
    EmployeeSC(QString &dbName, Employee* employee, QWidget *parent = 0);
    ~EmployeeSC();

private:
    Ui_EmployeeSC ui;

	log_errors* journal;

	Employee* userData;
	BillingPeriod *currentPeriod;
	PayForm curPayForm;

private:
	//конструкторы

	void initialDBManager(QString dbName);

	bool showEmployeeData();

	void error_msg(const char* short_description, const char* text);
	void parseBaseDataObject(HireDirective *hd, QString dutyChartName,BillingPeriod *currentPeriod);
	
	void fillTabelMarks(PayForm pf);
	void fillTabelDateValues(QDate &date);
	void fillTabelMarksValues(QDate &date);

	void setDescription(LaborSheet& laborSheet);

private slots:
	void showPeriod(QDate date);
	void setCurrentPeriod();

	void editMarksList();
	void saveMarksList();
	void cancelMarksList();

};
#endif // EMPLOYEESC_H
