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
private:

    Ui_SalaryCount *ui; // не самый при€тный способ, зато все видно из коробки
    void switchMode(app_states state);
    void saveEditableEntries(LaborSheet* obj);
    LaborSheet* shapeDataObject();
	// текущий отображаемый расчЄтный период
	BillingPeriod* _viewedPeriod;

	// текущие параметры мес€ца (дл€ более оптимального обновлени€ виджетов при переключении на новый мес€ц)
	int _startDayOfWeek , _monthLength;
	QList<QComboBox*> _comboboxes; // список максимум из 31 комбобоксов дл€ каждого дн€ мес€ца

	/*! ѕеревыдать комбобоксы на €чейки таблицы редактирвани€ отметок */
	void regenMarksCalendar();
private slots:

    void showSelectedItem(int row);
	void periodDateChanged(QDate date); // TODO: connect to dateEdit
};

#endif // SALARYCOUNTLABORSHEET_H
