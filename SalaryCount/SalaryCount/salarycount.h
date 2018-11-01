#ifndef SALARYCOUNT_H
#define SALARYCOUNT_H

#include <QtWidgets/QMainWindow>
#include <qmessagebox.h>
#include "employee.h"
#include "ui_salarycount.h"

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
	void updateWorkListActions();
	void showStacketItem(int indexPage, QString namePage);

private slots:
	//поведение на странице создания графиков
	void addDutyChart();//добавление нового графика
	void changePayForm(int index);

	void saveNewDutyChart();
	void cancelNewDutyChart();

	//переходы по страницам приложения
	void showEmployeesPage();//страница со списком сотрудников
	void showLaborSheetsPage();//страница табелей учета труда
	void showDutyChartsPage();//страница графиков работы 
	void showHireDirectivesPage();//страница приказов
};

#endif // SALARYCOUNT_H
