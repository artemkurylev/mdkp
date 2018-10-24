#ifndef MARK_H
#define MARK_H

#include "dbrecord.h"

class Mark : public DbRecord
{
    Q_OBJECT

public:
    Mark();
    Mark(int baseMark);
    ~Mark();

	enum Type
	{
		HOLIDAY = 100,
		ATTENDS = 124,
		MISS = 0,
		USUAL = 8,
		INVALID = 999,
	};

	// inherited
	bool fetch();
	bool set();
	bool validate() const;
	bool update() const;

	// getters
	int base()		const	{	return _base;		}
	int altered()	const	{	return _altered;	}

	// methods

private:
    int _base;
    int _altered;
};

#endif // MARK_H
