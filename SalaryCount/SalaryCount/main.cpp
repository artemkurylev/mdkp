#include "salarycount.h"
#include "employeesc.h"
#include <QtWidgets/QApplication>
#include <QtCore/QCoreApplication>

#include "companyopendialog.h"
#include "unittest/DirectiveGeneratorTest.h"
#include <CalcTest.h>

int test_main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	if(true) // if tests enabled
	{
		return test_main(argc, argv);
	}

	//DirectiveGenerator g;
	//HireDirective hd;

	//g.pdf( &hd, "example.pdf" );
	
	//DirectiveGeneratorTest dgt(0);
	//QTest::qExec( &dgt , NULL , NULL);
	
    QApplication a(argc, argv);
    companyOpenDialog q;
    q.show();
    //SalaryCount w;
    //w.show();
    return a.exec();
}

int test_main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	freopen ("sc_stderr.log","w",stderr);
	freopen ("sc_stdout.log","w",stdout);
	

	fprintf (stderr, "This sentence is redirected to a file.");
	printf ("This sentence is redirected to a file.");

	CalcTest t;
	QTest::qExec( &t , NULL , NULL);


	fclose (stderr);
    return 0; // a.exec();
}