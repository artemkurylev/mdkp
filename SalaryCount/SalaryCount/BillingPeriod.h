#ifndef BILLINGPERIOD_H
#define BILLINGPERIOD_H

#include <QObject>
#include<qdatetime.h>
#include"dbrecord.h"

//! ��������� ������
class BillingPeriod : public DbRecord
{
    Q_OBJECT

public:
    BillingPeriod(const QDate& startDate);
	BillingPeriod(int id) : DbRecord(id) {}

	//! ������ ���������� �������
    enum Status
	{
		NOT_OPENED,	/*< ��� �� ��� ������ */
		OPEN,		/*< ������ � ��������� ������ (�������) */
		CLOSED,		/*< ������ */
		MODIFIED	/*< ������ ����� �������� � ������� ���������� �������� */
	};

    BillingPeriod(const QDate& startDate, Status status);
    BillingPeriod(int id, const QDate& startDate, Status status);
    ~BillingPeriod();

	// getters
    enum Status status()		{	return _status;		}
	const QDate& startDate()	{	return _startDate;	}

	// methods
    bool fetch();
	bool set() ;
	bool validate() const;
	bool update() const;
    int insert();
   
    static bool createDbTable();
	static long countEntries();
    static BillingPeriod* getByDate(const QDate& date);
    static BillingPeriod* getCurrentPeriod();

	//! ���������� ��������
	void open();
	void close();
	void set_modified();

	//! ��������/������� ��������� ��������� ������
	BillingPeriod* nextPeriod();

    
private:
	// �������
    enum Status _status;
    QDate _startDate;

	// singleton-��� ������
	BillingPeriod* _next; //! <default> = NULL;  ��������� ��������� ������
};

#endif // BILLINGPERIOD_H
