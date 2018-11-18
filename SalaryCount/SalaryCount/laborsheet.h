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
    int award()const {return this->_award;}
	
	// сеттеры
	void setBillingPeriodId(int billingPeriodId) { this->_billingPeriodId = billingPeriodId;}
    void setEmployeeeId(int employeeeId)	{ this->_employeeId = employeeeId;}
    void setDutyChartId(int dutyChartId)	{ this->_dutyChartId = dutyChartId;}
    void setAward(float award)	{ this->_award = award;}
	
    /*! Getter для взятия всех отметок табеля. */
    const QList<Mark>& grid()  const{return this->_grid;}

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
	int countBaseTimeUnits();
	/*! Подсчитать отработанное время за период
	*/

	int countActualTimeUnits ();
	
	// TODO! сделать метод(ы?) для получения рассчитываемой статистики

	/*! заносит изменённые поля всех отметок в основные и сбрасывает изменения */
	void commitChanges();


    //Наследуемые методы
    int LaborSheet::insert();
    bool LaborSheet::update() const;
    bool LaborSheet::fetch();
    bool LaborSheet::validate() const;

    //! Сеттер для оценок
    void setGrid(QList<Mark> list){_grid = list;}

	// Статические методы
    static bool createDbTable();

    static QMap <int,int> getAll();

    static long countEntries();

    static QList<LaborSheet> getByPeriodId(int id);
private:
	// столбцы
    int _employeeId, _billingPeriodId;
	int _dutyChartId; //!< график сотрудника для этого месяца (в другие может измениться)
	float _award; /*! выплата за месяц */

	// отметки (привязанные по внешнему ключу)
    QList<Mark> _grid;

	// singleton-указатели на связанные записи
    BillingPeriod* _billingPeriod;
	Employee* _employee;
    DutyChart* _dutyChart;

};

#endif // LABORSHEET_H
