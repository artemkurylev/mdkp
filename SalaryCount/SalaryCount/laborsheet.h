#ifndef LABORSHEET_H
#define LABORSHEET_H

#include "dbrecord.h"
#include "mark.h"
#include "dutychart.h"
#include "qdatetime.h"
#include "employee.h"

/*������ ������ �� ���� �����
*/
class LaborSheet : public DbRecord
{
    Q_OBJECT

public:
    LaborSheet(QObject *parent);
    ~LaborSheet();

    LaborSheet(int employeeId);
	bool fillWithDefaults();
    /*
        Getter ��� ������ ���� ������� ������.
    */
    const QList<Mark>& marks() const{return _grid;}
    /*
        getter ��� ������ ����
    */
    const QDate beginDate() const{return this->_beginDate;}
    /*
        getter ��� ������ �������
    */
    const DutyChart* dutyChart() const{return this->_dutyChart;}
	bool fillWithDefaults(int empploeeId, QDate date,DutyChart* dutyChart);
    const Employee* employee() const;
    /*!
        Getter ��� ������ ���� ������� ������.
    */
    const QList<Mark>* marks() const{return &grid;}

	/*! ���������� �������� ������� ����� �� ������
	*/
	int countDefaultTimeUnits() const;

	/*! ���������� ������������ ����� �� ������
	*/
	int countActualTimeUnits () const;

private:
    QDate _beginDate;
    int employeeId;
    QList<Mark> grid; 
    DutyChart* _dutyChart;
};

#endif // LABORSHEET_H
