#include <CalcTest.h>


void CalcTest::normal()
{
	// create
	QCOMPARE(1,1);

	qDebug("un test normal");

	QCOMPARE(0,1);
}










//#include <cfixcc.h>
//class CalcTest : public cfixcc::TestFixture
//{
//private:
//
//public:
//	static void SetUp()
//	{
//	}
//
//	static void TearDown()
//	{
//	}
//
//	void Before()
//	{
//	}
//
//	void After()
//	{
//	}
//
//	void Test()
//	{
//		//CFIX_INCONCLUSIVE(__TEXT("Not implemented"));
//	}
//	void NormalLaborSheet()
//	{
//		CFIXCC_ASSERT_EQUALS(1,1);
//	}
//};
//
//CFIXCC_BEGIN_CLASS(CalcTest)
//	CFIXCC_METHOD(Test)
//	CFIXCC_METHOD(NormalLaborSheet)
//CFIXCC_END_CLASS()
//
