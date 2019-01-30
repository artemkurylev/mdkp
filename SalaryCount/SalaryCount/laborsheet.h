#ifndef LABORSHEET_H
#define LABORSHEET_H

#include "dbrecord.h"
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
    LaborSheet(QObject *parent, int employeeId);


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
