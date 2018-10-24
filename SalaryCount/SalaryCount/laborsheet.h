#ifndef LABORSHEET_H
#define LABORSHEET_H

#include "dbrecord.h"
#include "dutychart.h"
#include "qdatetime.h"
#include "employee.h"
/*Личный табель на один месяц
*/
class LaborSheet : public DbRecord
{
    Q_OBJECT

public:
    LaborSheet(QObject *parent);
    ~LaborSheet();
    LaborSheet(QObject *parent, int employeeId);


	bool fillWithDefaults(int empploeeId, QDate date,DutyChart* dutyChart);
    const Employee* employee() const;
    /*!
        Getter для взятия всех отметок табеля.
    */
    const QList<Mark>* marks() const{return &grid;}

	/*! Подсчитать плановое рабочее время за период
	*/
	int countDefaultTimeUnits() const;

	/*! Подсчитать отработанное время за период
	*/
	int countActualTimeUnits () const;

private:
    QDate _beginDate;
    int employeeId;
    QList<Mark> grid; 
    DutyChart* _dutyChart;
};

#endif // LABORSHEET_H
