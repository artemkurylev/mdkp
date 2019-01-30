#ifndef BILLINGPERIOD_H
#define BILLINGPERIOD_H

#include <QObject>
#include<qdatetime.h>
#include"dbrecord.h"
class BillingPeriod : public DbRecord
{
    Q_OBJECT

public:
    BillingPeriod(const QDate& startDate);
    ~BillingPeriod();

	// getters
    int status()	{	return _status;		}
	const QDate& startDate()		{	return _startDate;	}

	// methods
    bool fetch();
	bool set() ;
	bool validate() const;
	bool update() const;

	//! ���������� ��������
	void open();
	void close();
	void set_modified();

	enum Status
	{
		NOT_OPENED,	/*< ��� �� ��� ������ */
		OPEN,		/*< ������ � ��������� ������ (�������) */
		CLOSED,		/*< ������ */
		MODIFIED	/*< ������ ����� �������� � ������� ���������� �������� */
	};

private:

    enum Status _status;
    QDate _startDate;
};

#endif // BILLINGPERIOD_H
