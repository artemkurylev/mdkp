#include "salarycount.h"
#include "employeesc.h"
#include <QtWidgets/QApplication>


#include "DirectiveGenerator.h"


int main(int argc, char *argv[])
{

	//DirectiveGenerator g;
	//HireDirective hd();

	//g.pdf( &hd, "example.pdf" );
	
	/*DirectiveGeneratorTest dgt(0);
	QTest::qExec( &dgt , NULL , NULL);*/

    QApplication a(argc, argv);
    SalaryCount w;
    w.show();
    return a.exec();
}
