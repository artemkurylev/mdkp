#ifndef LABORSHEET_H
#define LABORSHEET_H

#include "dbrecord.h"
#include "mark.h"
#include "dutychart.h"
#include "qdatetime.h"
#include "employee.h"
#include "BillingPeriod.h"

/*! Личный табель на один месяц
*/
class LaborSheet : public DbRecord
{
    Q_OBJECT

public:

    LaborSheet();
    LaborSheet(int employeeId, int billingPeriodId);
    LaborSheet(const LaborSheet &laborsheet);
    LaborSheet(int id, int billingPeriodId, int employeeId, QList<Mark> grid);
    ~LaborSheet();

	// геттеры
	int billingPeriodId()const {return this->_billingPeriodId;}
    int employeeeId()const {return this->_employeeId;}
    int dutyChartId()const {return this->_dutyChartId;}
	
	// сеттеры
	void setBillingPeriodId(int billingPeriodId) { this->_billingPeriodId = billingPeriodId;}
    void setEmployeeeId(int employeeeId)	{ this->_employeeId = employeeeId;}
    void setDutyChartId(int dutyChartId)	{ this->_dutyChartId = dutyChartId;}
	
    /*! Getter для взятия всех отметок табеля. */
    const QList<Mark>& marks() const{return this->_grid;}
    /*! Ещё один Getter для взятия всех отметок табеля. */
    QList<Mark> grid()  const{return this->_grid;}

    /*! getter для взятия даты
    */
    const QDate& startDate() const{return this->_billingPeriod->startDate();}
    /*! getter для взятия графика
    */

    const DutyChart* dutyChart() const	{return this->_dutyChart;}

    Employee* employee();
    BillingPeriod* billingPeriod();
    PayForm payForm();
	DutyChart* dutyChart();

	bool fillWithDefaults();
	bool fillWithDefaults(int employeeId, const QDate& date,DutyChart* dutyChart);
	
	/*! Подсчитать плановое рабочее время за период
	*/
	int countDefaultTimeUnits();
	/*! Подсчитать отработанное время за период
	*/

	int countActualTimeUnits ();

    //Наследуемые методы
    int LaborSheet::insert();
    bool LaborSheet::update() const;
    bool LaborSheet::fetch();
    bool LaborSheet::validate() const;
    
	// Статические методы
    static bool createDbTable();

    static QMap <int,int> getAll();

    static long countEntries();

    static QList<LaborSheet> getByPeriodId(int id);
private:
	// столбцы
    int _employeeId, _billingPeriodId;
	int _dutyChartId; //!< график сотрудника для этого месяца (в другие может измениться)

	// отметки (привязанные по внешнему ключу)
    QList<Mark> _grid;

	// singleton-указатели на связанные записи
    BillingPeriod* _billingPeriod;
	Employee* _employee;
    DutyChart* _dutyChart;

};

#endif // LABORSHEET_H
