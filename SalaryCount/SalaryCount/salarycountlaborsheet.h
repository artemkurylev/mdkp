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
    void editLaborSheet();
    void saveEditedLabor();
	void cancelEditLabor();
private:

    Ui_SalaryCount *ui; // не самый приятный способ, зато все видно из коробки
    void switchMode(app_states state);
    void saveEditableEntries(LaborSheet* obj);
    LaborSheet* shapeDataObject();
	// текущий отображаемый расчётный период
	BillingPeriod* _viewedPeriod;

	// для текущей конфигурации месяца
	QList<QComboBox*> _comboboxes; // список максимум из 31 комбобоксов для каждого дня месяца

	/*! Перевыдать комбобоксы на ячейки таблицы редактирвания отметок */
	void regenMarksCalendar();
private slots:

    void showSelectedItem(int row);

    void goToCurrentPeriod();

};

#endif // SALARYCOUNTLABORSHEET_H
