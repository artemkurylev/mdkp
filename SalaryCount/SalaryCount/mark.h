#ifndef MARK_H
#define MARK_H

#include "dbrecord.h"


class Mark : public DbRecord
{
    Q_OBJECT

public:

    Mark();

//    Mark(int id); // create & fetch
//    Mark(int dutyChartId,int laborsheetId=NULL, int base=HOLIDAY, int altered=INVALID, int countHours=0, int alteredCountHours=-1);
    Mark(int baseMark);
	Mark(const Mark &mark);
    Mark(int base, int altered, int countHours, int alteredCountHours, int dutychartId = 0,int laborsheetId = 0);
    ~Mark();

    bool fetch();
    bool validate() const;
    bool set();
    bool update() const;

	enum Type
	{
		HOLIDAY = 100,
		ATTENDS = 1, // ������ ��� ������������ ���������� ���� ��� ���������� ����� ������
		MISS = 0,
		USUAL = 8, // ����������� 8-������� ���� (���������� �� ���������)
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
	bool isAltered()const	{	return _altered != INVALID;	}
    int countHours()		const	{	return _countHours;		}
    int alteredCountHours()	const	{	return _alteredCountHours;	}
    bool isAlteredCountHours()const {	return _alteredCountHours != -1;	}
    int dutyChartId()	const	{	return _dutyChartId;	}
    int laborsheetId()	const	{	return _laborsheetId;	}

	// setters
	void setBaseMark(int base)			{	_base = base;			}
	void setAlteredMark(int altered)	{	_altered = altered;		}
    void setCountHours(int hrs)			{	_countHours = hrs;		}
    void setAlteredCountHours(int hrs)	{	_alteredCountHours=hrs;	}
    void setDutyChartId(int id)			{	_dutyChartId = id;		}
    void setLaborsheetId(int id)		{	_laborsheetId = id;		}
    void setId(int id)                  {   _id = id;               }
	
	// methods
	/*! ������� ��������� ���� � �������� � ���������� ��������� */
	void commitChanges();
	void resetAltered()
	{
		_altered = INVALID;
		_alteredCountHours = -1;
	}

private:
    int _base;
    int _altered;
    int _countHours;
    int _alteredCountHours;
    int _dutyChartId;
    int _laborsheetId;
};

#endif // MARK_H
