#include "salarycount.h"
#include <QtWidgets/QApplication>
#include <QtTest/QtTest>

#include "unittest/DirectiveGeneratorTest.h"


int main(int argc, char *argv[])
{
	QTest::qExec( new DirectiveGeneratorTest(0) , NULL , NULL);

    //QApplication a(argc, argv);
    //SalaryCount w;
    //w.show();
    //return a.exec();
}
