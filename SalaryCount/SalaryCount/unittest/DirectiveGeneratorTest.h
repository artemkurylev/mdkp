#ifndef DirectiveGeneratorTest_H
#define DirectiveGeneratorTest_H

#include <QObject>
#include <QtTest/QtTest>
#include <QtWidgets/QApplication>

#include "DirectiveGenerator.h"


class DirectiveGeneratorTest : public QObject
{
	Q_OBJECT

public:
	DirectiveGeneratorTest(QObject *parent);
	~DirectiveGeneratorTest();

private:
	DirectiveGenerator *generator;


private slots:
	//void cleanup();
    void normal();

};

#endif // DirectiveGeneratorTest_H
