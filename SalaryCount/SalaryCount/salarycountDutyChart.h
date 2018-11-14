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
	Ui_SalaryCount *ui;//не самый приятный способ, зато все видно из коробки

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
	//поведение на странице создания графиков
	void addDutyChart();//добавление нового графика
	void editDutyChart();
	void cancelNewDutyChart();
	void saveNewDutyChart();//метод работает с бд
	void deleteDutyChart(int row);

	void changePayForm(int index);

	void showSelectedItem(int row);
};

#endif // SALARYCOUNTDUTYCHART_H