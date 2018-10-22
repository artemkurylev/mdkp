#include "salarycount.h"
#include <QtWidgets/QApplication>

#include "DirectiveGenerator.h"


int main(int argc, char *argv[])
{
	DirectiveGenerator g;
	HireDirective hd();

	g.pdf( &hd, "example.pdf" );
	
	//QApplication a(argc, argv);
    //SalaryCount w;
    //w.show();
    //return a.exec();
}
