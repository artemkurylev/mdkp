#ifndef SALARYCOUNTDUTYCHART_H
#define SALARYCOUNTDUTYCHART_H

#include "delegateStates.h"
#include "dutychart.h"

class salarycountDutyChart : public delegateStates
{
	Q_OBJECT

public:
	salarycountDutyChart(Ui_SalaryCount *ui);
	~salarycountDutyChart();

private:
	Ui_SalaryCount *ui;//не самый приятный способ, зато все видно из коробки

private:
	DutyChart* shapeDataObject();
	void validateData() const;
	void loadListItems() const {}
	void updateListItems() const {}
	void clearFields();

private slots:
	//поведение на странице создания графиков
	void addDutyChart();//добавление нового графика
	void editDutyChart();
	void saveNewDutyChart();
	void cancelNewDutyChart();

	void changePayForm(int index);

	//void showSelectedItem();
		
};

#endif // SALARYCOUNTDUTYCHART_H