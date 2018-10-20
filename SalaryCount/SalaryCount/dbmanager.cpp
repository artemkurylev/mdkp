#include "dbmanager.h"

DbManager::DbManager(QObject *parent)
    : QObject(parent)
{

}
DbManager::DbManager(QObject *parent,QString hostName, QString dbName, int port, QString pass){
    this->db.addDatabase("QMYSQL");
    this->db.setDatabaseName(dbName);
    this->db.setHostName(hostName);
    this->db.setPort(port);
    this->db.setPassword(pass);
}

DbManager::~DbManager()
{

}

