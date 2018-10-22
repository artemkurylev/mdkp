#include "dbrecord.h"

DbRecord::DbRecord(QObject *parent)
    : QObject(parent)
{

}
DbRecord::DbRecord(int id)
{
	this->_id = id;
	//this->fetch();
}
DbRecord::DbRecord(const DbRecord & other)
{
	//*this = other;
}

int DbRecord::id()
{
    return _id;
}
DbRecord::~DbRecord()
{

}
