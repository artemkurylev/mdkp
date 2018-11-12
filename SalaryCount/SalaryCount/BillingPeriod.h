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
    enum Status
	{
		NOT_OPENED,	/*< Ещё не был открыт */
		OPEN,		/*< Открыт в настоящий момент (активен) */
		CLOSED,		/*< Закрыт */
		MODIFIED	/*< Изменён после закрытия и ожидает повторного закрытия */
	};

    BillingPeriod(const QDate& startDate, Status status);
    ~BillingPeriod();

	

	// getters
    enum Status status()		{	return _status;		}
	const QDate& startDate()	{	return _startDate;	}

	// methods
    bool fetch();
	bool set() ;
	bool validate() const;
	bool update() const;
    static bool createDbTable();
    int insert() const;

	//! Управление статусом
	void open();
	void close();
	void set_modified();

private:

    enum Status _status;
    QDate _startDate;
};

#endif // BILLINGPERIOD_H
