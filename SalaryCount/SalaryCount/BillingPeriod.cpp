#include "BillingPeriod.h"

BillingPeriod::BillingPeriod(const QDate& startDate)
    : DbRecord(0)
{
	_status = NOT_OPENED;
	_startDate = startDate;
} 
BillingPeriod::~BillingPeriod()
{

}

bool BillingPeriod::fetch()
{
    return false;
}
bool BillingPeriod::set()
{
    return false;
}
bool BillingPeriod::validate() const
{
    return false;
}
bool BillingPeriod::update() const
{
    return false;
}

void BillingPeriod::open()
{
	_status = OPEN;
}
void BillingPeriod::close()
{
	_status = CLOSED;
}
void BillingPeriod::set_modified()
{
	_status = MODIFIED;
}
