#include "salarycount.h"
#include "employeesc.h"
#include <QtWidgets/QApplication>
#include <QtCore/QCoreApplication>

#include "companyopendialog.h"
#include "unittest/DirectiveGeneratorTest.h"
#include <CalcTest.h>

int test_main(int argc, char *argv[]);
void redirect_output_streams();

int main(int argc, char *argv[])
{
	redirect_output_streams();

	if(false) // if tests enabled
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

void redirect_output_streams()
{
	freopen ("sc_stderr.log","w",stderr); // можно задать 'w+' для дозаписи (чтобы прошлые логи не затирались)
	freopen ("sc_stdout.log","w",stdout);
	
	fprintf(stderr, "Begin of STDERR log.\n");
	printf ("Begin of STDOUT log.\n");
}


int test_main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	CalcTest t;
	QTest::qExec( &t , NULL , NULL);

    return 0; // a.exec();
}