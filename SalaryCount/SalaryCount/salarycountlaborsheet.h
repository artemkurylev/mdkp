#ifndef SALARYCOUNTLABORSHEET_H
#define SALARYCOUNTLABORSHEET_H

#include "delegateStates.h"
#include "laborsheet.h"
#include"BillingPeriod.h"
#include<qtablewidget.h>
class salarycountLaborSheet : public delegateStates
{
    Q_OBJECT

public:
	salarycountLaborSheet(Ui_SalaryCount *ui, QString name="");
    ~salarycountLaborSheet();

public slots:
	void updateInfo(QString name);
	void periodDateChanged(const QDate& date);
	void closePeriod();

private:
    Ui_SalaryCount *ui; // �� ����� �������� ������, ���� ��� ����� �� �������
    void switchMode(app_states state);
	// ������� ������������ ��������� ������
	BillingPeriod* _viewedPeriod;

	// ������� ��������� ������ (��� ����� ������������ ���������� �������� ��� ������������ �� ����� �����)
	int _startDayOfWeek , _monthLength;
	QList<QComboBox*> _comboboxes; // ������ �������� �� 31 ����������� ��� ������� ��� ������

	/*! ���������� ���������� �� ������ ������� ������������� ������� */
	void regenMarksCalendar();
private slots:
    void showLabor();
};

#endif // SALARYCOUNTLABORSHEET_H
