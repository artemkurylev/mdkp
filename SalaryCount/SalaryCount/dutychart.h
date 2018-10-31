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
    
	DutyChart(QList<Mark> marks){_grid = marks;}

	bool fetch() {return false;}
	bool set() {return false;}
	bool validate() const {return false;}
	bool update() const {return false;}
    int insert() const{return -1;}
    static bool createDbTable();

    const QDate anchorDate() const	{return _anchorDate;}
    const int length()		 const	{return _grid.size();}
    const QList<Mark>& grid() const	{return _grid;}

   ~DutyChart();

private:

private:
    

    QList<Mark> _grid;
    QDate _anchorDate;
};

#endif // DUTYCHART_H
