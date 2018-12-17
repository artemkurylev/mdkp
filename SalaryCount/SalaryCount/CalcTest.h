#pragma once


#include <QObject>
#include <QtTest/QtTest>

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> eec4bb5... Частичная реализация инициализации для тестирования Табеля
#include "dutychart.h"
#include "laborsheet.h"
#include "BillingPeriod.h"
#include "BookKeeper.h"
<<<<<<< HEAD
=======
>>>>>>> 3690967... Добавлен класс для тестирования расчётов
=======
>>>>>>> eec4bb5... Частичная реализация инициализации для тестирования Табеля

class CalcTest : public QObject
{
	Q_OBJECT

public:
<<<<<<< HEAD
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
=======
	CalcTest(QObject *parent = 0);
>>>>>>> eec4bb5... Частичная реализация инициализации для тестирования Табеля
	~CalcTest() {};

private:
	BillingPeriod *billPeriod;
	LaborSheet *laborSheet;
	Employee *guy;
	DutyChart * chart;
	HireDirective *hireDir;

private slots:
	void initTestCase();
	//void init();
	void cleanupTestCase();
	//void cleanup();
    void normal();
>>>>>>> 3690967... Добавлен класс для тестирования расчётов

};

