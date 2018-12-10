#ifndef SALARYCOUNTGUITESTER_H
#define SALARYCOUNTGUITESTER_H

#include <QObject>
#include <QtTest/QtTest>
#include "ui_salarycount.h"
#include <QtWidgets/QApplication>

class SalaryCountGuiTester: public QObject
{
	Q_OBJECT

public:
	SalaryCountGuiTester(Ui_SalaryCount *ui);
	~SalaryCountGuiTester();

private:
	Ui_SalaryCount *ui; 

private slots:
	
	void init();
	void cleanup();

	void exitAction();
	void editWorkSchedule();
	void deleteWorkSchedule();
	void addNewWorkSchedule();
	void addWorker();
	void editWorkerInfo();
	void editLaborSheet();
	void showOrder();








};
#endif  SALARYCOUNTGUITESTER_H
