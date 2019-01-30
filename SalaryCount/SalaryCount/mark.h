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
