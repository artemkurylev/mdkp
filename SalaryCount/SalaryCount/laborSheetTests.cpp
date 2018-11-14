#include <cfixcc.h>
#include<qlist.h>
#include "laborsheet.h"

class laborSheetTests : public cfixcc::TestFixture
{
private:

	bool compareMarks(const QList<Mark>* real, QList<Mark> &exist)
	{
		if(real->count() == exist.count())
		{
			int count = real->count();
			for(int i=0; i<count; ++i)
			{
				if( real->at(i)!=exist.at(i) )
				{
					return false;
				}
			}
		}
		return false;
	}

public:
	void baseFillWithDefault()
	{
		LaborSheet* sheet = new LaborSheet();
		
		bool result = sheet->fillWithDefaults();

		if(!result)
		{
			CFIX_ASSERT_MESSAGE(result==false, L"«аполнение по умолчанию не было произведено");
		}

		QList<Mark> exist;
		exist.append(Mark::Type::ATTENDS);
		exist.append(Mark::Type::ATTENDS);
		exist.append(Mark::Type::HOLIDAY);

		CFIX_ASSERT( compareMarks(sheet->marks(),exist) );
	}


};

CFIXCC_BEGIN_CLASS(laborSheetTests)
	CFIXCC_METHOD(baseFillWithDefault)


CFIXCC_END_CLASS()
