#pragma once


#include <QObject>
#include <QtTest/QtTest>

#include "dutychart.h"
#include "laborsheet.h"
#include "BillingPeriod.h"
#include "BookKeeper.h"

class CalcTest : public QObject
{
	Q_OBJECT

public:
	CalcTest(QObject *parent = 0);
	~CalcTest() {};

private:
	BillingPeriod *billPeriod;
	LaborSheet *laborSheet;
	Employee *guy;
	DutyChart * chart;
	HireDirective *hireDir;

private slots:
	void initTestCase();
	void init();
	void cleanupTestCase();
	//void cleanup();

    void normal();
    void OneZeroMark();
    void DefaultSheet();

};

