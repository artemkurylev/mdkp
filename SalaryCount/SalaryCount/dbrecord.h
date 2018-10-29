#ifndef DBRECORD_H
#define DBRECORD_H

#include <QObject>

class DbRecord : public QObject
{
    Q_OBJECT

public:
    DbRecord(QObject *parent);

   ~DbRecord();

	/*! Запросить запись из БД [SELECT] (обновить локальную копию)
	*/
    virtual bool fetch() = 0;
    
	///*! Задать данные записи, не отправляя из в БД (обновить локальную копию)
	//*/
 //   virtual bool set() = 0;
    
	/*! Проверить данные записи на корректность (полезно перед отправкой в БД)
	*/
    virtual bool validate() const = 0;
    
	/*! Отправить запись в БД [UPDATE]
	*/
    virtual bool update() const = 0;

	/*! Возвращает ID [Primary Key] записи в БД
	*/
    int id() const;

    /*! Строка для запроса к базе данных MYSQL */
    QString _query;
    DbManager _manager;
    int _id;
private:


    virtual bool validate() = 0;
    
    virtual bool update() = 0;


private:
    
};

#endif // DBRECORD_H
