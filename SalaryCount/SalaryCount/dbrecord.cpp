#include "dbrecord.h"

DbRecord::DbRecord()
    : QObject(0)
{
	this->_id = -1;
	this->free_records_on_destroy = true;
}
DbRecord::DbRecord(int id)
{
	this->_id = id;
	this->free_records_on_destroy = true;
	this->fetch();
}
DbRecord::DbRecord(const DbRecord & other)
{
	this->free_records_on_destroy = false;
	//*this = other;
}

int DbRecord::id() const
{
    return _id;
}
DbRecord::~DbRecord()
{

}
