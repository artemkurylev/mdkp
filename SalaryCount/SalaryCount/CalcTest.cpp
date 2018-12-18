#include "CalcTest.h"


CalcTest::CalcTest(QObject *parent)
	: QObject(parent)
{
	this->billPeriod = NULL;
	this->laborSheet = NULL;
	this->guy = NULL;
	this->chart = NULL;
	this->hireDir = NULL;

	//Employee(QString _fio,QString _phoneNumber,long long _INN,int _currentDutyChartID,int _hireDirectiveID, QString _pass);
}

void CalcTest::initTestCase()
{
	QString fio("Тестов Тест Иванович");
	float salary = 1000.0;
	PayForm payForm = PER_HOUR;

	int hd_id = 123,
		emp_id = 405,
		chart_id = 202,
		sheet_id = 202,
		billp_id = 307
		;

	// create all
	this->billPeriod = new BillingPeriod(billp_id, QDate(2010,5,01), BillingPeriod::OPEN);


	this->hireDir = new HireDirective(hd_id, QDate(2010,3,01), fio, payForm, salary, /*employeeId*/0 );

	this->laborSheet = new LaborSheet(sheet_id, billp_id, /*employeeId*/0, QList<Mark>() /*grid*/);

	this->chart = new DutyChart(chart_id);
	*chart = defaultChart();

	this->guy = new Employee(fio,"+7 (123) 505 33 99", 123456789012L /*INN*/, chart_id, hd_id, "an md5 hash");


//	BillingPeriod* _billingPeriod;
//	Employee* _employee;
//	DutyChart* _dutyChart;
	this->laborSheet->_billingPeriod = this->billPeriod;
	this->laborSheet->_employee = this->guy;
	this->laborSheet->_dutyChart = this->chart;

	//Employee* _hiredEmployee; //! <default> = NULL;  приказ
	this->hireDir->_hiredEmployee = this->guy;
	this->guy->_hireDirective = this->hireDir;

	this->laborSheet->fillWithDefaults();

}
void CalcTest::cleanupTestCase()
{
	if(this->billPeriod != NULL)
		delete this->billPeriod;

	if(this->laborSheet != NULL)
		delete this->laborSheet;

	if(this->guy != NULL)
		delete this->guy;

	if(this->chart != NULL)
		delete this->chart;

	if(this->hireDir != NULL)
		delete this->hireDir;

}


void CalcTest::normal()
{
	/*! Подсчитать плановое рабочее время за период
	int countBaseTimeUnits();
	*/
	/*! Подсчитать отработанное время за период
	int countActualTimeUnits ();
	*/
	
	qDebug("countBaseTimeUnits: %d", this->laborSheet->countBaseTimeUnits());
	qDebug("countActualTimeUnits: %d", this->laborSheet->countActualTimeUnits());

	// create
	QCOMPARE(this->laborSheet->countBaseTimeUnits(), this->laborSheet->countActualTimeUnits() );

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
