#include "dbmanager.h"

DbManager::DbManager(QString hostName, QString dbName, int port, QString pass){
    this->db.addDatabase("QMYSQL");
    this->db.setDatabaseName(dbName);
    this->db.setHostName(hostName);
    this->db.setPort(port);
    this->db.setPassword(pass);
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

DbManager::~DbManager()
{

}

