#pragma once


#include <QObject>
#include <QtTest/QtTest>


class CalcTest : public QObject
{
	Q_OBJECT

public:
	CalcTest(QObject *parent = 0)
		: QObject(parent) {};
	~CalcTest() {};

private:
	//DirectiveGenerator *generator;


private slots:
	//void cleanup();
    void normal();

};

