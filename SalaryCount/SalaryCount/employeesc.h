#ifndef EMPLOYEESC_H
#define EMPLOYEESC_H

#include <QtWidgets/QMainWindow>
#include <qmessagebox.h>
#include "delegateStates.h"
#include "employee.h"
#include"laborsheet.h"
#include "ui_employeesc.h"

class EmployeeSC : public QMainWindow//, public delegateStates
{
    Q_OBJECT

private:
	//QAction* currentAction;

	//Employee* shapeDataObject();
	//void parseDataObject(Employee *obj);

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
	void initialDBManager();

signals:
	/*void cancelChanges();
	void saveChanges();
	void showPaget(QString name);*/

private slots:

	//void updateInfo(QString name);
	//void rememberState(bool state);

};
#endif // EMPLOYEESC_H
