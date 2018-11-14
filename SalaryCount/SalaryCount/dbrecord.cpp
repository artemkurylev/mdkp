#include "dbrecord.h"

DbRecord::DbRecord()
    : QObject(0)
{

}
DbRecord::DbRecord(int id)
{
	this->_id = id;
	this->fetch();
}
DbRecord::DbRecord(const DbRecord & other)
{
	//*this = other;
}

int DbRecord::id() const
{
    return _id;
}
DbRecord::~DbRecord()
{

}
