#ifndef DBRECORD_H
#define DBRECORD_H

#include <QObject>
#include "dbmanager.h"

class DbRecord : public QObject
{
    Q_OBJECT

public:
    DbRecord();
	DbRecord(int id);
	DbRecord(const DbRecord & other);
    ~DbRecord();
    

	/*! ��������� ������ �� �� [SELECT] (�������� ��������� �����)
	*/
    virtual bool fetch() = 0;
    
	///*! ������ ������ ������, �� ��������� �� � �� (�������� ��������� �����)
	//*/
 //   virtual bool set() = 0;
    
	/*! ��������� ������ ������ �� ������������ (������� ����� ��������� � ��)
	*/
    virtual bool validate() const = 0;
    
	/*! ��������� ������ � �� [UPDATE]
	*/
    virtual bool update() const = 0;

	/*! ���������� ID [Primary Key] ������ � ��
	*/
    int id() const;
protected:

    /*! ������ ��� ������� � ���� ������ MYSQL */
    QString query;

private:
    int _id;

    

};

#endif // DBRECORD_H
