#ifndef LABORSHEET_H
#define LABORSHEET_H

#include "dbrecord.h"
#include "mark.h"
#include "dutychart.h"
#include "qdatetime.h"
#include "employee.h"
#include "BillingPeriod.h"

/*Личный табель на один месяц
*/
class LaborSheet : public DbRecord
{
    Q_OBJECT

public:
    LaborSheet();
    ~LaborSheet();
    LaborSheet(int employeeId);
    LaborSheet(BillingPeriod* billingPeriod,int employeeId,QList<Mark> grid,DutyChart* _dutyChart);
	bool fillWithDefaults();
    /*
        Getter для взятия всех отметок табеля.
    */
    const QList<Mark>& marks() const{return _grid;}
    /*
        getter для взятия даты
    */
    const QDate beginDate() const{return this->_billingPeriod->startDate();}
    /*
        getter для взятия графика
    */
    const DutyChart* dutyChart() const{return this->_dutyChart;}
	bool fillWithDefaults(int empploeeId, QDate date,DutyChart* dutyChart);
    const Employee* employee() const;
    PayForm payForm() const;

	/*! Подсчитать плановое рабочее время за период
	*/
	int countDefaultTimeUnits() const;

	/*! Подсчитать отработанное время за период
	*/
	int countActualTimeUnits () const;
    //Наследуемые методы
    int LaborSheet::insert() const;
    bool LaborSheet::update() const;
    bool LaborSheet::fetch();
    bool LaborSheet::validate() const;
    //Статические методы
    static bool createDbTable();
    static QMap <int,int> getAll();
private:
    BillingPeriod* _billingPeriod;
    int _employeeId;
    QList<Mark> _grid;
    DutyChart* _dutyChart;
};

#endif // LABORSHEET_H
