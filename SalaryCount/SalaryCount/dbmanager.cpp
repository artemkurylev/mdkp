#include "dbmanager.h"

DbManager::DbManager(QString hostName, QString dbName, int port,QString userName, QString pass){
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
bool DbManager::makeQuery(QSqlQuery* query){
    if(query->isValid())
    {
        query->exec();
        return true;
    }
    else
    {
        return false;
    }
}
bool DbManager::checkConnection(){
    if(db.isOpen()){
        return true;
    }
    else{
        QString s= db.lastError().text();
        s += "as";
    }
}
DbManager::~DbManager()
{

}

