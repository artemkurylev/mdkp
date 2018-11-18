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

	//! Статус Расчётного периода
    enum Status
	{
		NOT_OPENED,	/*< Ещё не был открыт */
		OPEN,		/*< Открыт в настоящий момент (активен) */
		CLOSED,		/*< Закрыт */
		MODIFIED	/*< Изменён после закрытия и ожидает повторного закрытия */
	};

	BillingPeriod(int id) : DbRecord(id) {}
    BillingPeriod(const QDate& startDate);
    BillingPeriod(const QDate& startDate, Status status);
    BillingPeriod(int id, const QDate& startDate, Status status);
    BillingPeriod(const BillingPeriod& other);
    ~BillingPeriod();

	// getters
    enum Status status() 	const	{	return _status;		}
	const QDate& startDate() const	{	return _startDate;	}

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
    static QPair<QDate,QDate> getDateSpan(); /*!< минимальная и максимальная даты периодов */

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
