#ifndef SALARYCOUNTDUTYCHART_H
#define SALARYCOUNTDUTYCHART_H

#include "delegateStates.h"
#include "dutychart.h"

class salarycountDutyChart : public delegateStates
{
	Q_OBJECT

public:
	salarycountDutyChart(Ui_SalaryCount *ui, QString name="");
	~salarycountDutyChart();

private:
	Ui_SalaryCount *ui;//�� ����� �������� ������, ���� ��� ����� �� �������

private:
	//@Override
	DutyChart* shapeDataObject();
	void parseDataObject(const DutyChart* obj);

	//
	void clearFields();
	void switchMode(app_states state);
	void saveNewEntries(DutyChart* obj);
	void saveEditableEntries(DutyChart* obj);
	
public slots:
	void updateInfo(QString name);

private slots:
	//��������� �� �������� �������� ��������
	void addDutyChart();//���������� ������ �������
	void editDutyChart();
	void cancelNewDutyChart();
	void saveNewDutyChart();//����� �������� � ��
	void deleteDutyChart(int row);

	void changePayForm(int index);

	void showSelectedItem(int row);
};

#endif // SALARYCOUNTDUTYCHART_H