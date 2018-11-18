#ifndef SALARYCOUNTEMPLOYEES_H
#define SALARYCOUNTEMPLOYEES_H

#include "delegateStates.h"
#include "employee.h"
#include "BillingPeriod.h"
#include "HireDirective.h"
#include "dutychart.h"

class salarycountEmployees : public delegateStates
{
	Q_OBJECT

public:
	salarycountEmployees(Ui_SalaryCount *ui, QString name="");
	~salarycountEmployees();

private:
	Ui_SalaryCount *ui;//не самый приятный способ, зато все видно из коробки

private:
	//@Override
	Employee* shapeDataObject();
	void parseDataObject(const Employee* obj);

	//
	void clearFields();
	bool fillDutyChartComboBox();
	void switchMode(app_states state);
	void saveNewEntries(Employee* obj);
	void saveEditableEntries(Employee* obj);

	//
	QDate getMinimumRecipientDate();
	int getNewHireDirectiveNumber();
	
public slots:
	void updateInfo(QString name);

private slots:
	//поведение на странице создания графиков
	void addEmployee();//добавление нового графика
	void editEmployee();
	void cancelNewEmployee();
	void saveNewEmployee();//метод работает с бд
	void deleteEmployee();

	void changePayForm(int index);

	void showSelectedItem(int row);
	
};

#endif // SALARYCOUNTEMPLOYEES_H
