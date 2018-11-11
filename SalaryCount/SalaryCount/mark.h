#ifndef MARK_H
#define MARK_H

#include "dbrecord.h"

class Mark : public DbRecord
{
    Q_OBJECT

public:
    Mark();
    Mark(int baseMark);
    Mark(int base, int altered, int dutychartId,int laborsheetId);
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
	bool set();
	bool validate() const;
	bool update() const;
    int insert() const;
    static bool createDbTable();
	// getters
	int base()		const	{	return _base;		}
	int altered()	const	{	return _altered;	}

	// methods

private:
    int _base;
    int _altered;
    int _dutychartId;
    int _laborsheetId;
};

#endif // MARK_H
