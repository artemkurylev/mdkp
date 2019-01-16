#ifndef SALARYCOUNT_H
#define SALARYCOUNT_H

#include <QtWidgets/QMainWindow>
#include <qmessagebox.h>
#include "employee.h"
#include"laborsheet.h"
#include "ui_salarycount.h"
#include "company.h"
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
    SalaryCount(QString dbName, QWidget *parent = 0);
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

	//������������
	void initialDBManager();
    void initialDBManager(QString dbName);

signals:
	void cancelChanges();
	void saveChanges();
	void showPaget(QString name);

private slots:

	void rememberState(bool state);

	//! �������� �� ��������� ����������
	void showPage(QAction* actionEmited);
	//! ���� "����"
	void showCompanyDialog(QAction* actionEmited);
};
#endif // SALARYCOUNT_H
