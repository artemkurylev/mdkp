<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> eec4bb5... Частичная реализация инициализации для тестирования Табеля
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

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> bf4b070... Отладочная печать табеля для тестов
void CalcTest::init()
{
	this->laborSheet->fillWithDefaults();
}

<<<<<<< HEAD
=======
>>>>>>> eec4bb5... Частичная реализация инициализации для тестирования Табеля
=======
>>>>>>> bf4b070... Отладочная печать табеля для тестов
void CalcTest::initTestCase()
{
	QString fio("������ ���� ��������");
	float salary = 1000.0;
	PayForm payForm = PER_HOUR;

	int hd_id = 123,
		emp_id = 405,
		chart_id = 202,
		sheet_id = 202,
		billp_id = 307
		;

	// create all
<<<<<<< HEAD
<<<<<<< HEAD
	this->billPeriod = new BillingPeriod(billp_id, QDate(2018,12,01), BillingPeriod::OPEN);
=======
	this->billPeriod = new BillingPeriod(billp_id, QDate(2010,5,01), BillingPeriod::OPEN);
>>>>>>> eec4bb5... Частичная реализация инициализации для тестирования Табеля
=======
	this->billPeriod = new BillingPeriod(billp_id, QDate(2018,12,01), BillingPeriod::OPEN);
>>>>>>> bf4b070... Отладочная печать табеля для тестов


	this->hireDir = new HireDirective(hd_id, QDate(2010,3,01), fio, payForm, salary, /*employeeId*/0 );

	this->laborSheet = new LaborSheet(sheet_id, billp_id, /*employeeId*/0, QList<Mark>() /*grid*/);

	this->chart = new DutyChart(chart_id);
	*chart = defaultChart();
<<<<<<< HEAD
	chart->_id = chart_id;
=======
>>>>>>> eec4bb5... Частичная реализация инициализации для тестирования Табеля

	this->guy = new Employee(fio,"+7 (123) 505 33 99", 123456789012L /*INN*/, chart_id, hd_id, "an md5 hash");


//	BillingPeriod* _billingPeriod;
//	Employee* _employee;
//	DutyChart* _dutyChart;
	this->laborSheet->_billingPeriod = this->billPeriod;
	this->laborSheet->_employee = this->guy;
	this->laborSheet->_dutyChart = this->chart;

	//Employee* _hiredEmployee; //! <default> = NULL;  ������
	this->hireDir->_hiredEmployee = this->guy;
	this->guy->_hireDirective = this->hireDir;

<<<<<<< HEAD
<<<<<<< HEAD
	//this->laborSheet->fillWithDefaults();
=======
	this->laborSheet->fillWithDefaults();
>>>>>>> eec4bb5... Частичная реализация инициализации для тестирования Табеля
=======
	//this->laborSheet->fillWithDefaults();
>>>>>>> bf4b070... Отладочная печать табеля для тестов

}
void CalcTest::cleanupTestCase()
{
	if(this->billPeriod != NULL)
		delete this->billPeriod;

	if(this->laborSheet != NULL)
<<<<<<< HEAD
	{
		this->laborSheet->_employee = NULL;
		this->laborSheet->_billingPeriod = NULL;
		this->laborSheet->_dutyChart = NULL;
		delete this->laborSheet;
	}

	if(this->guy != NULL)
	{
		this->guy->_hireDirective = NULL;
		delete this->guy;
	}
=======
		delete this->laborSheet;

	if(this->guy != NULL)
		delete this->guy;
>>>>>>> eec4bb5... Частичная реализация инициализации для тестирования Табеля

	if(this->chart != NULL)
		delete this->chart;

	if(this->hireDir != NULL)
<<<<<<< HEAD
	{
		this->hireDir->_hiredEmployee = NULL;
		delete this->hireDir;
	}

}

QString mark2String_perhour(const Mark& m, bool base, bool altered)
{
	QString r;
	int v;
	if(base)
		r += QString::number(m.countHours());
	if(altered && base)
		r += "/";
	if(altered)
		r += QString::number(m.alteredCountHours());

	return r;
}

QString mark2String_permonth(const Mark& m, bool base, bool altered)
{
	QString r;
	int v;
	if(base)
		r += QString::number(m.base());
	if(altered && base)
		r += "/";
	if(altered)
		r += QString::number(m.altered());

	return r;
}

void printCanendar(LaborSheet* ls, bool base = true, bool altered = false, bool perHours=true)
{
	int monthLen = ls->grid().size();
	int dayOfWeek = ls->startDate().dayOfWeek() - 1;
	int w = base&&altered? 5 : 2;

	QString r;
	for(int i=0; i < monthLen+dayOfWeek; ++i)
	{
		if(i%7 ==0)
			r += "\n";

		r += QString("[%1]").arg(
			i<dayOfWeek ?
			base&&altered? "-----" : "--"
			:
			perHours?
				mark2String_perhour(ls->grid()[i-dayOfWeek],base,altered)
				: mark2String_permonth(ls->grid()[i-dayOfWeek],base,altered)
			, w);
	}


	qDebug("%s", r.toLocal8Bit().data());
}

void CalcTest::normal()
{
	/*! ���������� �������� ������� ����� �� ������
	int countBaseTimeUnits();
	*/
	/*! ���������� ������������ ����� �� ������
	int countActualTimeUnits ();
	*/
	
	qDebug("countBaseTimeUnits:   %d", this->laborSheet->countBaseTimeUnits());
	qDebug("countActualTimeUnits: %d", this->laborSheet->countActualTimeUnits());

	printCanendar(this->laborSheet, true, true);
	printCanendar(this->laborSheet, true, true, false);

	QCOMPARE( laborSheet->countBaseTimeUnits(), laborSheet->countActualTimeUnits() );
}

void CalcTest::OneZeroMark()
{
	this->laborSheet->_grid[5].setAlteredCountHours( 0 );

	qDebug("countBaseTimeUnits:   %d", this->laborSheet->countBaseTimeUnits());
	qDebug("countActualTimeUnits: %d", this->laborSheet->countActualTimeUnits());

	printCanendar(this->laborSheet, true, true);
	printCanendar(this->laborSheet, true, true, false);

	this->laborSheet->commitChanges();
	qDebug("Changes commited");

	printCanendar(this->laborSheet, true, true);
	printCanendar(this->laborSheet, true, true, false);

	QCOMPARE( laborSheet->countBaseTimeUnits(), laborSheet->countActualTimeUnits() );

}

void CalcTest::DefaultSheet()
{
	{
		LaborSheet def_lbsh(*this->laborSheet);
		def_lbsh.fillWithDefaults();

		qDebug("defaultSheet :");

		//printCanendar(&def_lbsh, true, true);
		//printCanendar(&def_lbsh, true, true, false);

		QCOMPARE( def_lbsh.countBaseTimeUnits(), def_lbsh.countActualTimeUnits() );

		// �� ������� ������ ��� ����������� def_lbsh
		def_lbsh._employee = NULL;
		def_lbsh._billingPeriod = NULL;
		def_lbsh._dutyChart = NULL;
	}

	qDebug("def_lbsh seems to be destroyed.");


	QList<LaborSheetDescriptionLine> descr = this->laborSheet->description();

	QString hr;
	foreach(const LaborSheetDescriptionLine& line , descr)
	{
		//QString name , default_value, base_value, altered_value;
		//float value; // -1 �������� ���������� �������� � ���� ����
		hr += QString("\n name: %1, %2 / %3 / %4. value: %5")
			.arg(line.name, line.default_value, line.base_value, line.altered_value).arg(line.value);
	}

	qDebug(hr.toLocal8Bit().data());
=======
#include <CalcTest.h>
=======
		delete this->hireDir;

}
>>>>>>> eec4bb5... Частичная реализация инициализации для тестирования Табеля

QString mark2String_perhour(const Mark& m, bool base, bool altered)
{
	QString r;
	int v;
	if(base)
		r += QString::number(m.countHours());
	if(altered && base)
		r += "/";
	if(altered)
		r += QString::number(m.alteredCountHours());

	return r;
}

QString mark2String_permonth(const Mark& m, bool base, bool altered)
{
	QString r;
	int v;
	if(base)
		r += QString::number(m.base());
	if(altered && base)
		r += "/";
	if(altered)
		r += QString::number(m.altered());

	return r;
}

void printCanendar(LaborSheet* ls, bool base = true, bool altered = false, bool perHours=true)
{
	int monthLen = ls->grid().size();
	int dayOfWeek = ls->startDate().dayOfWeek() - 1;
	int w = base&&altered? 5 : 2;

	QString r;
	for(int i=0; i < monthLen+dayOfWeek; ++i)
	{
		if(i%7 ==0)
			r += "\n";

		r += QString("[%1]").arg(
			i<dayOfWeek ?
			base&&altered? "-----" : "--"
			:
			perHours?
				mark2String_perhour(ls->grid()[i-dayOfWeek],base,altered)
				: mark2String_permonth(ls->grid()[i-dayOfWeek],base,altered)
			, w);
	}


	qDebug("%s", r.toLocal8Bit().data());
}

void CalcTest::normal()
{
	/*! ���������� �������� ������� ����� �� ������
	int countBaseTimeUnits();
	*/
	/*! ���������� ������������ ����� �� ������
	int countActualTimeUnits ();
	*/
	
	qDebug("countBaseTimeUnits:   %d", this->laborSheet->countBaseTimeUnits());
	qDebug("countActualTimeUnits: %d", this->laborSheet->countActualTimeUnits());

	printCanendar(this->laborSheet, true, true);
	printCanendar(this->laborSheet, true, true, false);

	// create
	QCOMPARE(this->laborSheet->countBaseTimeUnits(), this->laborSheet->countActualTimeUnits() );
}

void CalcTest::OneZeroMark()
{
	this->laborSheet->_grid[0].setAlteredCountHours( 0 );

	qDebug("countBaseTimeUnits:   %d", this->laborSheet->countBaseTimeUnits());
	qDebug("countActualTimeUnits: %d", this->laborSheet->countActualTimeUnits());

	// create
	QCOMPARE(this->laborSheet->countBaseTimeUnits(), this->laborSheet->countActualTimeUnits() );

<<<<<<< HEAD
	QCOMPARE(0,1);
>>>>>>> 3690967... Добавлен класс для тестирования расчётов
=======
>>>>>>> eec4bb5... Частичная реализация инициализации для тестирования Табеля
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
