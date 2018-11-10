#ifndef DUTYCHART_H
#define DUTYCHART_H

#include <QObject>
#include <qdatetime.h>
#include "BookKeeper.h"
#include "mark.h"

class DutyChart : public DbRecord
{
    Q_OBJECT

public:
    DutyChart(/* int id ?? */);
    
	DutyChart(QList<Mark> marks, enum PayForm payForm=PER_HOUR)	{_grid = marks;_payForm=payForm;}

	bool fetch()	{return false;}
	bool set()		{return false;}
	bool validate() const {return false;}
	bool update()	const {return false;}
    int insert()	const ;
    static bool createDbTable();

    const int payForm()		 const	{return _payForm;}
    const QDate anchorDate() const	{return _anchorDate;}
    const int length()		 const	{return _grid.size();}
    const QList<Mark>& grid() const	{return _grid;}

    ~DutyChart();

   
private:
    
	//! Форма оплаты, для которой создаётся график 
	int _payForm;
    QList<Mark> _grid;
    QDate _anchorDate;
};

#endif // DUTYCHART_H
