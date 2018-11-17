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
	Employee(QString _fio,QString _phoneNumber,int _INN,int _currentDutyChartID,int _hireDirectiveID);
    ~Employee();

    bool fetch();
    bool validate() const;
    bool update() const;
    int insert();

    static bool createDbTable();
    static QMap<int,QString> getAll();
    static long countEntries();
    HireDirective* hireDirective();

    //�������
    const QString& fio() const{return _fio;}
    const QString& phoneNumber() const {return _phoneNumber;}
    const int inn()const {return _INN;};
    const int currentDutyChartID() const{return _currentDutyChartID;}
    const int nextDutyChartID()const {return _nextDutyChartID;}
    const QDate& nextDutyChartSince() const{return _nextDutyChartSince;}
    const int hireDirectiveID() const {return _hireDirectiveID;}
private:
	// ������
    QString _fio;
    QString _phoneNumber;
    int _INN;

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
