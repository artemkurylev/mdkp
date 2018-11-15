#ifndef MARK_H
#define MARK_H

#include "dbrecord.h"

class Mark : public DbRecord
{
    Q_OBJECT

public:
    Mark();
    Mark(int id); // create & fetch
    Mark(int dutyChartId,int laborsheetId=NULL, int base=HOLIDAY, int altered=INVALID, int countHours=0, int alteredCountHours=-1);
    ~Mark();

	enum Type
	{
		HOLIDAY = 100,
		ATTENDS = 1, // удобно при суммировании посещённых дней для помесячной формы оплаты
		MISS = 0,
		USUAL = 8, // стандартный 8-часовой день (предлагать по умолчанию)
		INVALID = 999,
	};

	// inherited
	bool fetch();
	bool validate() const;
	bool update() const;
    int insert();
    static bool createDbTable();

	// getters
	int base()		const	{	return _base;		}
	int altered()	const	{	return _altered;	}
    int countHours()		const	{	return _countHours;		}
    int alteredCountHours()	const	{	return _alteredCountHours;	}
    int dutyChartId()	const	{	return _dutyChartId;	}
    int laborsheetId()	const	{	return _laborsheetId;	}

	// setters
	void setBaseMark(int base)			{	_base = base;			}
	void setAlteredMark(int altered)	{	_altered = altered;		}
    void setCountHours(int hrs)			{	_countHours = hrs;		}
    void setAlteredCountHours(int hrs)	{	_alteredCountHours=hrs;	}
    void setDutyChartId(int id)			{	_dutyChartId = id;		}
    void setLaborsheetId(int id)		{	_laborsheetId = id;		}

	// methods

private:
    int _base;
    int _altered;
    int _countHours;
    int _alteredCountHours;
    int _dutyChartId;
    int _laborsheetId;
};

#endif // MARK_H
