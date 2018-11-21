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


void DirectiveGeneratorTest::normal()
{
	QTextCodec * codec=QTextCodec::codecForLocale();
	// create
	DirectiveGenerator generator;
	HireDirective hd(QDate(22,10,2018), QString(codec->toUnicode("Ибрагим  Исмаил   Адаму")), PER_HOUR, 15000, 1234);
	generator.pdf( &hd, "normal.pdf");
}
