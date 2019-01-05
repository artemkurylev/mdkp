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

	// глобальный указатель на основное окно приложени€
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

	//конструкторы
    void initialDBManager(QString dbName = 0);

signals:
	void cancelChanges();
	void saveChanges();
	void showPaget(QString name);

public slots:
	//! переходы по страницам приложени€
	void showPage(QAction* actionEmited);

	//! “естирование
	void startTesting();

private slots:
	void rememberState(bool state);
	//! меню "‘айл"
	void showCompanyDialog(QAction* actionEmited);

};
#endif // SALARYCOUNT_H
