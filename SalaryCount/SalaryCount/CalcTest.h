#pragma once


#include <QObject>
#include <QtTest/QtTest>

<<<<<<< HEAD
#include "dutychart.h"
#include "laborsheet.h"
#include "BillingPeriod.h"
#include "BookKeeper.h"
=======
>>>>>>> 3690967... Добавлен класс для тестирования расчётов

class CalcTest : public QObject
{
	Q_OBJECT

public:
<<<<<<< HEAD
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
=======
	CalcTest(QObject *parent = 0)
		: QObject(parent) {};
	~CalcTest() {};

private:
	//DirectiveGenerator *generator;


private slots:
	//void cleanup();
    void normal();
>>>>>>> 3690967... Добавлен класс для тестирования расчётов

};

