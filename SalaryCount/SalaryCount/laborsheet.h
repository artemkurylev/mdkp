#ifndef LABORSHEET_H
#define LABORSHEET_H

#include "dbrecord.h"
#include "mark.h"
#include "dutychart.h"
#include "qdatetime.h"
#include "employee.h"
#include "BillingPeriod.h"

/*������ ������ �� ���� �����
*/
class LaborSheet : public DbRecord
{
    Q_OBJECT

public:
    LaborSheet(QObject *parent);
    ~LaborSheet();

    LaborSheet(int employeeId);
    LaborSheet(int id, int billingPeriodId, int employeeId, QList<Mark> grid);
	bool fillWithDefaults();
    /*
        Getter ��� ������ ���� ������� ������.
    */
    const QList<Mark>& marks() const{return _grid;}
    /*
        getter ��� ������ ����
    */
    const QDate beginDate() const{return this->_billingPeriod->startDate();}
    /*
        getter ��� ������ �������
    */
    const DutyChart* dutyChart() const{return this->_dutyChart;}

	bool fillWithDefaults(int emploeeId, QDate date,DutyChart* dutyChart);
    Employee* employee();
    BillingPeriod* billingPeriod();
    PayForm payForm();

	/*! ���������� �������� ������� ����� �� ������
	*/
	int countDefaultTimeUnits();

	/*! ���������� ������������ ����� �� ������
	*/

	int countActualTimeUnits ();

    //����������� ������
    int LaborSheet::insert();
    bool LaborSheet::update() const;
    bool LaborSheet::fetch();
    bool LaborSheet::validate() const;
    
	// ����������� ������
    static bool createDbTable();

    static QMap <int,int> getAll();

    static long countEntries();

    static QList<LaborSheet> getByPeriodId(int id);
private:
	// �������
    int _employeeId, _billingPeriodId;
	int _dutyChartId; // � ������, ��� ���� �� ����� (������������ ������� �� ������� `������-���-������-������`)

	// ������� (����������� �� �������� �����)
    QList<Mark> _grid;

	// singleton-��������� �� ��������� ������
    BillingPeriod* _billingPeriod;
	Employee* _employee;
    DutyChart* _dutyChart;
};

#endif // LABORSHEET_H
