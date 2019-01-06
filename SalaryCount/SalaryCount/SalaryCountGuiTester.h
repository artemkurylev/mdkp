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

class Tester : public QObject
{
	Q_OBJECT

public slots:
	void runTests(Ui_SalaryCount* ui);

signals:
	void testingFinished(int failedTests);
};


#endif  SALARYCOUNTGUITESTER_H
