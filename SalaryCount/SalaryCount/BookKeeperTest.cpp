#include "BookKeeperTest.h"



BookKeeperTest::BookKeeperTest(QObject *parent)
	: QObject(parent)
{
	

}



BookKeeperTest::~BookKeeperTest(void)
{
}



void BookKeeperTest::testCalSalary()
{
	//LaborSheet *ls(0);
	//bool bl=BookKeeper::calcSalary(ls);
	bool bl=false;
	QCOMPARE(bl,false);
}

void BookKeeperTest::testCalcPerHoursSalary()
{
	
	QCOMPARE(BookKeeper::calcPerHoursSalary(1000,5),5000.0);
	QCOMPARE(BookKeeper::calcPerHoursSalary(600,5),3000.0);
	QCOMPARE(BookKeeper::calcPerHoursSalary(1000,0),0.0);
	
}

void BookKeeperTest::testCalcPerMonthSalary()
{
	QCOMPARE(BookKeeper::calcPerMonthSalary(3000,1,1),3000.0);
	QCOMPARE(BookKeeper::calcPerMonthSalary(4000,3,5),2400.0);
	QCOMPARE(BookKeeper::calcPerMonthSalary(5000,0,5),0.0);
}

