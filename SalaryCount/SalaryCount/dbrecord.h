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
    DbRecord(QObject *parent);

   ~DbRecord();

	/*! ��������� ������ �� �� [SELECT] (�������� ��������� �����)
	*/
	virtual bool fetch() { return false; };
    
	///*! ������ ������ ������, �� ��������� �� � �� (�������� ��������� �����)
	//*/
 //   virtual bool set() = 0;
    
	/*! ��������� ������ ������ �� ������������ (������� ����� ��������� � ��)
	*/
    virtual bool validate() const = 0;
    
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

protected:
    /*! ������ ��� ������� � ���� ������ MYSQL */
    QString _query;
    int _id;

	////! ���������� ��������� - ��� ������� � �� ��� �������� ������ ������
	//const QString& tableName(); ??? �� �����

private:

private:
    
};

#endif // DBRECORD_H
