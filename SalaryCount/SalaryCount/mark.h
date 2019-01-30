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
		ATTENDS = 1, // ������ ��� ������������ ���������� ���� ��� ���������� ����� ������
		MISS = 0,
		USUAL = 8, // ����������� 8-������� ���� (���������� �� ���������)
		INVALID = 999,
	};

	void setBase(int state){base=state;}
	void setAltered(int state){altered=state;}

	// getters
	int base()		const	{	return _base;		}
	int altered()	const	{	return _altered;	}

	// methods

private:
    int _base;
    int _altered;
};

#endif // MARK_H
