#include "dbrecord.h"

DbRecord::DbRecord(QObject *parent)
    : QObject(parent)
{

}
int DbRecord::getId(){
    return id;
}
DbRecord::~DbRecord()
{

}
