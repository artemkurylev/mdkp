#ifndef LABORSHEET_H
#define LABORSHEET_H

#include "dbrecord.h"
#include "dutychart.h"
#include "qdatetime.h"
/*������ ������ �� ���� �����
*/
class LaborSheet : public DbRecord
{
    Q_OBJECT

public:
    LaborSheet(QObject *parent);
    ~LaborSheet();
    
	bool fillWithDefaults(int empploeeId, QDate date,DutyChart dutyChart);

private:
    
};

#endif // LABORSHEET_H
