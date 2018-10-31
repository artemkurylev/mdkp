#include "mark.h"

Mark::Mark()
    : DbRecord(0)
{

} 

Mark::Mark(int baseMark)
    : DbRecord(NULL)
{
	_base = baseMark;
	_altered = INVALID;
} 

bool Mark::fetch()
{
    return false;
}
bool Mark::set()
{
    return false;
}
bool Mark::validate() const
{
    return false;
}
bool Mark::update() const
{
    return false;
}
int Mark::insert() const
{
    return -1;
}
Mark::~Mark()
{

}
