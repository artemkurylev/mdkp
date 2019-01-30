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
#include "salarycountprofile.h"
class SalaryCount : public QMainWindow
{
    Q_OBJECT

private:
	QAction* currentAction;

public:
    SalaryCount(QString dbName = 0, QWidget *parent = 0);
    ~SalaryCount();

	// ���������� ��������� �� �������� ���� ����������
	static SalaryCount* globalApp;

private:

    Ui_SalaryCount ui;

	salarycountDutyChart* dutyChart;
	salarycountEmployees* employees;
    salarycountLaborSheet* laborSheet;
    salarycountDirectives* directives;
    SalaryCountProfile* profile;
	bool editState;

private:
	bool isEditable();
	void showStackedItem(QString namePage);

	//������������
    void initialDBManager(QString dbName = 0);

signals:
	void cancelChanges();
	void saveChanges();
	void showPaget(QString name);

public slots:
<<<<<<< HEAD
	//! �������� �� ��������� ����������
	void showPage(QAction* actionEmited);

	//! ������������
	void startTesting();
	void finishTesting(int failedTests);

signals:
	void runTestThread(Ui_SalaryCount* ui);

private slots:
	void rememberState(bool state);
	//! ���� "����"
	void showCompanyDialog(QAction* actionEmited);

=======
>>>>>>> 6406fd1... Добавлена функциональность "Начать работу" (кнопкой в профиле предприятия)
	//! �������� �� ��������� ����������
	void showPage(QAction* actionEmited);

private slots:
	void rememberState(bool state);
	//! ���� "����"
	void showCompanyDialog(QAction* actionEmited);

};
#endif // SALARYCOUNT_H
