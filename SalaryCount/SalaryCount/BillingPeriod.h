#ifndef BILLINGPERIOD_H
#define BILLINGPERIOD_H

#include <QObject>
#include<qdatetime.h>

class BillingPeriod : public DbRecord
{
    Q_OBJECT

public:
    BillingPeriod(const QDate& startDate);
    ~BillingPeriod();

	// getters
	enum Status status()	{	return _status;		}
	const QDate& startDate()		{	return _startDate;	}

	// methods

	//! Управление статусом
	void open();
	void close();
	void set_modified();

	enum Status
	{
		NOT_OPENED,	/*< Ещё не был открыт */
		OPEN,		/*< Открыт в настоящий момент (активен) */
		CLOSED,		/*< Закрыт */
		MODIFIED	/*< Изменён после закрытия и ожидает повторного закрытия */
	};

private:

    enum Status _status;
    QDate _startDate;
};

#endif // BILLINGPERIOD_H
