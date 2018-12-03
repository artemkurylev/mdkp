#ifndef EMPLOYEESC_H
#define EMPLOYEESC_H

#include <QtWidgets/QMainWindow>
#include <qmessagebox.h>
#include "employee.h"
#include"laborsheet.h"
#include "ui_employeesc.h"

class EmployeeSC : public QMainWindow
{
    Q_OBJECT

private:
	//QAction* currentAction;

public:
    EmployeeSC(QWidget *parent = 0);
    ~EmployeeSC();

private:
    Ui_EmployeeSC ui;

	//bool editState;

private:
	//bool isEditable();
	//void showStackedItem(QString namePage);

	//конструкторы
	//void initialDBManager();

signals:
	/*void cancelChanges();
	void saveChanges();
	void showPaget(QString name);*/

private slots:

	//void rememberState(bool state);

	//! переходы по страницам приложения
	//void showPage(QAction* actionEmited);
	//! меню "Файл"
	//void showCompanyDialog(QAction* actionEmited);
};
#endif // EMPLOYEESC_H
