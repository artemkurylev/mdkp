#include "DirectiveGeneratorTest.h"
#include "BookKeeper.h"
#include "HireDirective.h"

DirectiveGeneratorTest::DirectiveGeneratorTest(QObject *parent)
	: QObject(parent)
{
	//this->generator = generator;

}

DirectiveGeneratorTest::~DirectiveGeneratorTest()
{

}

//DirectiveGeneratorTest::void cleanup()
//{
//	if (this->generator)
//		delete this->generator;
//}


<<<<<<< HEAD
//void DirectiveGeneratorTest::normal()
//{
//	// create
//	DirectiveGenerator generator;
//	HireDirective hd(QDate(22,10,2018), QString("Ибрагим И.А."), PER_HOUR, 15000, 1234);
//	generator.pdf( &hd, "normal.pdf");
//}
=======

void DirectiveGeneratorTest::normal()
{
	// create
	DirectiveGenerator generator;
	HireDirective hd(5,QDate(22,10,2018), QString("Ибрагим И.А."), PER_HOUR, 15000, 1234);
	generator.pdf( &hd, "normal.pdf");
}

>>>>>>> 949f7c3... changed my hiredirective method normal
