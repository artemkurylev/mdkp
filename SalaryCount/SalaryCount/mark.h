#ifndef MARK_H
#define MARK_H

#include "dbrecord.h"


class Mark : public DbRecord
{
    Q_OBJECT

public:
    Mark(QObject *parent);
    Mark(int baseMark=0);
    ~Mark();

    bool fetch();
    bool validate() const;
    bool set();
    bool update() const;

	enum Type
	{
		HOLIDAY = 100,
		ATTENDS = 124,
		MISS = 0,
		USUAL = 8,
		INVALID = 999,
	};

	void setBase(int state){base=state;}
	void setAltered(int state){altered=state;}

private:
    int base;
    int altered;
};

#endif // MARK_H
