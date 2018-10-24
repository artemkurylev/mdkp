#ifndef LABORSHEET_H
#define LABORSHEET_H

#include "dbrecord.h"
#include "dutychart.h"
#include "qdatetime.h"
#include "employee.h"
/*Ћичный табель на один мес€ц
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
        Getter дл€ вз€ти€ всех отметок табел€.
    */
    const QList<Mark>* marks() const{return &grid;}

private:
    QDate beginDate;
    int employeeId;
    QList<Mark> grid; 
    DutyChart* dutyChart;
};

#endif // LABORSHEET_H
