#include "salarycount.h"
#include "employeesc.h"
#include <QtWidgets/QApplication>

#include "companyopendialog.h"
#include "DirectiveGenerator.h"
#include <CalcTest.h>


int main(int argc, char *argv[])
{
	//DirectiveGenerator g;
	//HireDirective hd();

	//g.pdf( &hd, "example.pdf" );
	
	/*DirectiveGeneratorTest dgt(0);
	QTest::qExec( &dgt , NULL , NULL);*/

    QApplication a(argc, argv);
    companyOpenDialog q;
    q.show();
    //SalaryCount w;
    //w.show();
    return a.exec();
}