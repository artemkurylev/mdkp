#ifndef DBRECORD_H
#define DBRECORD_H

#include <QObject>

#include "dbmanager.h"
#include <qsqlquery.h>
#include<qsqldatabase.h>
#include<qtablewidget.h>
#include <qsql.h>
#include<qvariant.h>

class CalcTest;

class DbRecord : public QObject
{
    Q_OBJECT

friend class CalcTest;

public:
    DbRecord(QObject *parent);

   ~DbRecord();

	/*! ��������� ������ �� �� [SELECT] (�������� ��������� �����)
	*/
	virtual bool fetch() { return false; };
    
	/*! ��������� ������ ������ �� ������������ (������� ����� ��������� � ��)
	*/
    virtual bool validate() const { return false; };
    
	/*! ��������� ������ � �� [UPDATE]
	*/
    virtual bool update() const = 0;

    /*! ������� ������ � ��
	@returns ID ��������� ������
    */
    virtual int insert() = 0;

	/*! ���������� ID [Primary Key] ������ � ��
	*/
    int id() const;

	DbRecord &DbRecord::operator =(const DbRecord & other) {_id = other.id(); return *this;};

protected:
    int _id;

private:

private:
    
};

#endif // DBRECORD_H
