#ifndef MARK_H
#define MARK_H

#include "dbrecord.h"

class Mark : public DbRecord
{
    Q_OBJECT

public:
    Mark(QObject *parent);
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

private:
    int base;
    int altered;
};

#endif // MARK_H
