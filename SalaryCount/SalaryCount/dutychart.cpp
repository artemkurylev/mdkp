#include "dutychart.h"

DutyChart::DutyChart()
    : DbRecord(0)
{
	// создать типичный график 5\2
	_grid.clear();
	_grid.reserve(7);
	for(int i=0 ; i<7 ; ++i )
	{
		if (i < 5)
			_grid.push_back(Mark::Type::USUAL);
		else
			_grid.push_back(Mark::Type::HOLIDAY);
	}
}

DutyChart::~DutyChart()
{

}
