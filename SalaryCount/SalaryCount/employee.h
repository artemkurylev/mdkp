#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QObject>
#include <qdatetime.h>
#include <qstring.h>
#include "dbrecord.h"
#include "dutychart.h"
#include "HireDirective.h"

class Employee : public DbRecord
{
    Q_OBJECT

public:
    Employee();
	Employee(int id);
    Employee(const Employee& employee);
	Employee(QString _fio,QString _phoneNumber,long long _INN,int _currentDutyChartID,int _hireDirectiveID);
    Employee(int id, QString _fio,QString _phoneNumber,long long _INN,int _currentDutyChartID,int _hireDirectiveID);
    ~Employee();

    bool fetch();
    bool validate() const;
    bool update() const;
    int insert();

    static bool createDbTable();
    static QMap<int,QString> getAll();
    static long countEntries();

    //�������
    const QString& fio() const{return _fio;}
    const QString& phoneNumber() const {return _phoneNumber;}
    const long long inn()const {return _INN;};
    const int currentDutyChartID() const{return _currentDutyChartID;}
    const int nextDutyChartID()const {return _nextDutyChartID;}
    const QDate& nextDutyChartSince() const{return _nextDutyChartSince;}
    const int hireDirectiveID() const {return _hireDirectiveID;}
    /* ����������� , ���� ������������ � ��������� ������ � � ������� ��� ��, �� ������ true, ����� false*/
    const bool auth() const;
    HireDirective* hireDirective();
	QDate hireDate()	{	return hireDirective()->hireDate();	}

	void setNextDutyChartSince(int nextDutyChartID,const QDate& nextDutyChartSince)
	{
		this->_nextDutyChartID = nextDutyChartID;
		this->_nextDutyChartSince = nextDutyChartSince;
	}
	void resetNextDutyChart()
	{
		this->_nextDutyChartID = 0;
		this->_nextDutyChartSince = QDate(); // set invalid date
	}

	/*! ��������� ����� ������� ����������, ���� ����� ���������� ���� � ����� ������.
	�������, ����� ������� ��������� ������ � ������ ���������� �������.
	\returns `true` ���� ������ ���� �������� � ��������� � ����������
	*/
	bool applyDutyChartChange(const QDate& currentPeriodStart);

private:
	// ������
    QString _fio;
    QString _phoneNumber;
    long long _INN;
    QString _password;
	// ������
    int _currentDutyChartID;
    int _nextDutyChartID;
    QDate _nextDutyChartSince;

	// DB links
	int _hireDirectiveID;

	//const QString& tableName() { return "employee";};

	// singleton-��� ������
	HireDirective* _hireDirective; //! <default> = NULL;  ������
};

#endif // EMPLOYEE_H
