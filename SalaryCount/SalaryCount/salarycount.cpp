#include "salarycount.h"

#include <QtTest/QtTest>
#include "unittest/DirectiveGeneratorTest.h"


SalaryCount::SalaryCount(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

		QTest::qExec( new DirectiveGeneratorTest(0) , NULL , NULL);
}

SalaryCount::~SalaryCount()
{

}
