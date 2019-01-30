#ifndef SALARYCOUNT_H
#define SALARYCOUNT_H

#include <QtWidgets/QMainWindow>

#include <qmessagebox.h>
#include "employee.h"
#include "ui_salarycount.h"
#include "BookKeeper.h"
#include "mark.h"
#include "dutychart.h"

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
	void addDutyChart();//���������� ������ �������
	void changePayForm(int index);

	void saveNewDutyChart();
	void cancelNewDutyChart();

	//

	//�������� �� ��������� ����������
	void showEmployeesPage();//�������� �� ������� �����������
	void showLaborSheetsPage();//�������� ������� ����� �����
	void showDutyChartsPage();//�������� �������� ������ 
	void showHireDirectivesPage();//�������� ��������
};

#endif // SALARYCOUNT_H
