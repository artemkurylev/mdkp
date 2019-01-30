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
    int countHours()		const	{	return _countHours;		}
    int alteredCountHours()	const	{	return _alteredCountHours;	}

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
