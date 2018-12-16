#ifndef EMPLOYEESC_H
#define EMPLOYEESC_H

#include <QtWidgets/QMainWindow>
#include <qmessagebox.h>
#include "delegateStates.h"
#include "employee.h"
#include "laborsheet.h"
#include "ui_employeesc.h"

class EmployeeSC : public QMainWindow//, public delegateStates
class EmployeeSC : public QMainWindow // , virtual public delegateStates
{
    Q_OBJECT

public:
    EmployeeSC(QString dbName, QWidget *parent = 0);
    ~EmployeeSC();

private:
    Ui_EmployeeSC ui;

	Employee* userData;

private:
	//bool isEditable();
	//void showStackedItem(QString namePage);

	//конструкторы
	void initialDBManager(QString dbName);

	//QAction* currentAction;

	Employee* shapeBaseDataObject();
	//void parseDataObject(Employee *obj);

private slots:

	//void updateInfo(QString name);
	//void rememberState(bool state);

};
#endif // EMPLOYEESC_H
