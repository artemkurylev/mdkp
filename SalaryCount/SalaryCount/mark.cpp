#include "mark.h"

Mark::Mark(QObject *parent)
    : DbRecord(parent)
{

} 

Mark::Mark(int baseMark)
    : DbRecord(NULL)
{
	base = baseMark;
} 

bool Mark::fetch(){
    return false;
}
bool Mark::validate(){
    return false;
}
bool Mark::set(){
    return false;
}
bool Mark::update(){
    return false;
}
Mark::~Mark()
{

}
