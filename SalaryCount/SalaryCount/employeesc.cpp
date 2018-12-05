#include "employeesc.h"

#include "dbmanager.h"
#include"qsqldatabase.h"

#include "unittest/DirectiveGeneratorTest.h"


EmployeeSC::EmployeeSC(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	//initialDBManager();
}

EmployeeSC::~EmployeeSC()
{
	
}