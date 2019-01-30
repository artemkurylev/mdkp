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
	Ui_SalaryCount *ui;//�� ����� �������� ������, ���� ��� ����� �� �������
	PayForm currentPayForm;

private:
	//@Override
	Employee* shapeDataObject();
	HireDirective* shapeHireDirective(int idEmployee);
	void parseDataObject(const Employee* obj);
	
	//
	void clearFields();
	bool fillDutyChartComboBox(PayForm pf);
	void switchMode(app_states state);
	void saveNewEntries(Employee* obj);
	void saveEditableEntries(Employee* obj);

	//
	
	int getNewHireDirectiveNumber();
public:
    QDate getMinimumRecipientDate();
public slots:
	void updateInfo(QString name);

private slots:
	//��������� �� �������� �������� ��������
	void addEmployee();//���������� ������ �������
	void editEmployee();
	void cancelNewEmployee();
	void saveNewEmployee();//����� �������� � ��
	//void deleteEmployee();

	void changePayForm(int index);

	void showSelectedItem(int row);
	
	//void innField();
};

#endif // SALARYCOUNTEMPLOYEES_H
