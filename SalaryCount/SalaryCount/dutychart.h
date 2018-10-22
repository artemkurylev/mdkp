#ifndef DUTYCHART_H
#define DUTYCHART_H

#include <QObject>
#include "mark.h"
#include<qdatetime.h>
class DutyChart : public DbRecord
{
    Q_OBJECT

public:
    DutyChart(QObject *parent);
    ~DutyChart();

private:
    int length()
	{
		return grid.size();
	}

    QList<Mark> grid;
    QDate anchorDate;
};

#endif // DUTYCHART_H
