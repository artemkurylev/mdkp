#ifndef DBRECORD_H
#define DBRECORD_H

#include <QObject>
#include "dbmanager.h"
#include <qsqlquery.h>
#include<qsqldatabase.h>
#include<qtablewidget.h>
#include <qsql.h>
#include<qvariant.h>

class DbRecord : public QObject
{
    Q_OBJECT

public:
    DbRecord();
	DbRecord(int id);
	DbRecord(const DbRecord & other);
    ~DbRecord();
    

	/*! Запросить запись из БД [SELECT] (обновить локальную копию)
	*/
	virtual bool fetch() { return false; };
    
	/*! Проверить данные записи на корректность (полезно перед отправкой в БД)
	*/
    virtual bool validate() const { return false; };
    
	/*! Отправить запись в БД [UPDATE]
	*/
    virtual bool update() const = 0;

    /*! Создать запись в БД
	@returns ID созданной записи
    */
    virtual int insert() = 0;

	/*! Возвращает ID [Primary Key] записи в БД
	*/
    int id() const;

	DbRecord &DbRecord::operator =(const DbRecord & other) {_id = other.id(); return *this;};

protected:
    int _id;

private:

};

#endif // DBRECORD_H
