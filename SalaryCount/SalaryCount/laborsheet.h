#ifndef LABORSHEET_H
#define LABORSHEET_H

#include "dbrecord.h"
#include "mark.h"
#include "dutychart.h"
#include "qdatetime.h"
#include "employee.h"

/*Личный табель на один месяц
*/
class LaborSheet : public DbRecord
{
    Q_OBJECT

public:
    LaborSheet();
    ~LaborSheet();
    LaborSheet(int employeeId);
	bool fillWithDefaults();
    /*
        Getter для взятия всех отметок табеля.
    */
    const QList<Mark>& marks() const{return _grid;}
    /*
        getter для взятия даты
    */
    const QDate beginDate() const{return this->_beginDate;}
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
private:
    QDate _beginDate;
    int employeeId;
    QList<Mark> _grid; 
    DutyChart* _dutyChart;
};

#endif // LABORSHEET_H
