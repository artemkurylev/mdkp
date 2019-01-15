#ifndef LABORSHEET_H
#define LABORSHEET_H

#include "dbrecord.h"
#include "mark.h"
#include "dutychart.h"
#include "qdatetime.h"
#include "employee.h"
#include "BillingPeriod.h"

struct LaborSheetDescriptionLine
{
	QString name , default_value, base_value, altered_value;
	float value; // -1 �������� ���������� �������� � ���� ����
};

/*! ������ ������ �� ���� �����
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

	// �������
	int billingPeriodId()const {return this->_billingPeriodId;}
    int employeeeId()const {return this->_employeeId;}
    int dutyChartId()const {return this->_dutyChartId;}
    int award()const {return this->_award;}
	
	// �������
	void setBillingPeriodId(int billingPeriodId) { this->_billingPeriodId = billingPeriodId;}
    void setEmployeeeId(int employeeeId)	{ this->_employeeId = employeeeId;}
    void setDutyChartId(int dutyChartId)	{ this->_dutyChartId = dutyChartId;}
    void setAward(float award)	{ this->_award = award;}
	
    /*! Getter ��� ������ ���� ������� ������. */
    const QList<Mark>& grid()  const{return this->_grid;}

    /*! getter ��� ������ ����
    */
    const QDate& startDate() {return billingPeriod()->startDate();}
    /*! getter ��� ������ �������
    */
	DutyChart* dutyChart();

    Employee* employee();
    BillingPeriod* billingPeriod();
    PayForm payForm();

	QList<LaborSheetDescriptionLine> description();

	bool fillWithDefaults();
	bool fillWithDefaults(int employeeId, const QDate& date,DutyChart* dutyChart);
	
	/*! ���������� �������� ������� ����� �� ������
	*/
	int countBaseTimeUnits();
	/*! ���������� ������������ ����� �� ������
	*/
	int countActualTimeUnits ();
	
	// TODO! ������� �����(�?) ��� ��������� �������������� ����������

	/*! ������� ��������� ���� ���� ������� � �������� � ���������� ��������� */
	void commitChanges();


    //����������� ������
    int LaborSheet::insert();
    bool LaborSheet::update() const;
    bool LaborSheet::fetch();
    bool LaborSheet::validate() const;

    //! ������ ��� ������
    void setGrid(QList<Mark> list){_grid = list;}

	// ����������� ������
    static bool createDbTable();
    static QMap <int,int> getAll();
    static long countEntries();
    static QList<LaborSheet> getByPeriodId(int id);
private:
	// �������
    int _employeeId, _billingPeriodId;
	int _dutyChartId; //!< ������ ���������� ��� ����� ������ (� ������ ����� ����������)
	float _award; /*! ������� �� ����� */

	// ������� (����������� �� �������� �����)
    QList<Mark> _grid;

	// singleton-��������� �� ��������� ������
    BillingPeriod* _billingPeriod;
	Employee* _employee;
    DutyChart* _dutyChart;

};

#endif // LABORSHEET_H
