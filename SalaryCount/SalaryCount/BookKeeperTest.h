#ifndef BookKeeperTest_H
#define BookKeeperTest_H

#include <QObject>
#include <QtTest/QtTest>
#include <QtWidgets/QApplication>

#include "BookKeeper.h"

class BookKeeperTest : public QObject
{
	Q_OBJECT

public:
	BookKeeperTest(QObject *parent);
	~BookKeeperTest();

private:

	private slots:
		void testCalSalary();
		void testCalcPerHoursSalary();
		void testCalcPerMonthSalary();
};

#endif 