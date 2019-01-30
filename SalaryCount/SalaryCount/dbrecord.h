#ifndef DBRECORD_H
#define DBRECORD_H

#include <QObject>

class DbRecord : public QObject
{
    Q_OBJECT

public:
    DbRecord(QObject *parent);

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

    /*! ������ ��� ������� � ���� ������ MYSQL */
    QString _query;
    DbManager _manager;
    int _id;
private:


    virtual bool validate() = 0;
    
    virtual bool update() = 0;


private:
    
};

#endif // DBRECORD_H
