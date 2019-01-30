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

	bool fillWithDefaults();
    Employee* getEmployee();
    /*
        Getter ��� ������ ���� ������� ������.
    */
    const QList<Mark>* marks() const{return &grid;}
    /*
        getter ��� ������ ����
    */
    QDate beginDate(){return this->_beginDate;}
    /*
        getter ��� ������ �������
    */
    const DutyChart* dutyChart() const{return this->_dutyChart;}
private:
    QDate _beginDate;
    int employeeId;
    QList<Mark> grid; 
    DutyChart* _dutyChart;
};

#endif // LABORSHEET_H
