#include "salarycount.h"

#include <QtTest/QtTest>
#include "dbmanager.h"
#include"qsqldatabase.h"

#include "unittest/DirectiveGeneratorTest.h"


SalaryCount::SalaryCount(QWidget *parent)
    : QMainWindow(parent)
{
    
    ui.setupUi(this);

    DbManager manager("localhost","salarycount",3306,"root","root");
    if(manager.checkConnection())
    {
        //Создание таблиц
        bool b = Employee::createDbTable();
        if(b)
        {

        }
    }
    else
    {

    }
	QTest::qExec( new DirectiveGeneratorTest(0) , NULL , NULL);
}

SalaryCount::~SalaryCount()
{

}
