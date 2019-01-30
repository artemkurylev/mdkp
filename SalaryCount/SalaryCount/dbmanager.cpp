#include "dbmanager.h"

DbManager::DbManager()
    : QObject(0)
{

}
/*static*/bool DbManager::singletonExists = false;
/*static*/DbManager* DbManager::globalManager = 0;

DbManager::DbManager(QString hostName, QString dbName, int port,QString userName, QString pass)
{
    this->db = QSqlDatabase::addDatabase("QMYSQL");
    this->db.setUserName(userName);
    this->db.setDatabaseName(dbName);
    this->db.setHostName(hostName);
    this->db.setPort(port);
    this->db.setPassword(pass);
    if(db.open()){
        QString str;
    }
    else{
        QString str = db.lastError().text();
        str+= "as";
    }

}
QSqlQuery* DbManager::makeQuery()
{
    return new QSqlQuery(this->db);
}
bool DbManager::checkConnection()
{
    if(db.isOpen())
    {
        return true;
    }
    else
    {
        QString s= db.lastError().text();
        return false;
    }
}


bool DbManager::checkConnection()
{
    if(db.isOpen()){
        return true;
    }
    else{
        QString s= db.lastError().text();
        return false;
    }
}
/*static*/ DbManager& DbManager::manager()
{
    if(!singletonExists)
    {
        if(true)
            DbManager::globalManager = new DbManager("localhost","salarycount",3306,"root","root");
        else
            DbManager::globalManager = new DbManager("109.206.169.214","salary_count",3306,"remote","!E3f5c712");
        DbManager::singletonExists = 1;
    }
    return *(DbManager::globalManager);
}
DbManager::~DbManager()
{

}

