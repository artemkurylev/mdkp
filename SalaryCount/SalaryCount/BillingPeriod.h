#ifndef BILLINGPERIOD_H
#define BILLINGPERIOD_H

#include <QObject>
#include<qdatetime.h>
#include"dbrecord.h"

//! Расчётный период
class BillingPeriod : public DbRecord
{
    Q_OBJECT

public:
    BillingPeriod(const QDate& startDate);
	BillingPeriod(int id) : DbRecord(id) {}

	//! Статус Расчётного периода
    enum Status
	{
		NOT_OPENED,	/*< Ещё не был открыт */
		OPEN,		/*< Открыт в настоящий момент (активен) */
		CLOSED,		/*< Закрыт */
		MODIFIED	/*< Изменён после закрытия и ожидает повторного закрытия */
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

	//! Управление статусом
	void open();
	void close();
	void set_modified();

	//! Получить/создать следующий расчётный период
	BillingPeriod* nextPeriod();

    
private:
	// столбцы
    enum Status _status;
    QDate _startDate;

	// singleton-кэш записи
	BillingPeriod* _next; //! <default> = NULL;  следующий расчётный период
};

#endif // BILLINGPERIOD_H
