#include "dbmanager.h"

struct DbConf loadDbConfig();
#include <QDateTime>
#include <QFile>
#include <QSettings>

DbManager::DbManager()
    : QObject(0)
{

}
/*static*/bool DbManager::singletonExists = false;
/*static*/DbManager* DbManager::globalManager = 0;

DbManager::DbManager(const QString& hostName, const QString& dbName, int port,const QString& userName, const QString& pass)
{
	// Сначала создаём БД
    this->db = QSqlDatabase::addDatabase("QMYSQL");
    this->db.setUserName(userName);
    //this->db.setDatabaseName(dbName);
    this->db.setHostName(hostName);
    this->db.setPort(port);
    this->db.setPassword(pass);
    if(this->db.open())
    {
        //QString str;
		QSqlQuery q(this->db);
		if( q.exec(tr("CREATE DATABASE IF NOT EXISTS %1;").arg(dbName) ) )
		{
			QString str = "Ok";
			this->db.close();
		}
		else
		{
			QString str = db.lastError().text();
			str+= "as";
		}
    }
    else
    {
        QString str = db.lastError().text();
        str+= "as";
    }

	// Теперь открываем нашу БД
    //this->db = QSqlDatabase::addDatabase("QMYSQL");
    //this->db.setUserName(userName);
    this->db.setDatabaseName(dbName);
    //this->db.setHostName(hostName);
    //this->db.setPort(port);
    //this->db.setPassword(pass);
    if(this->db.open())
    {
		QString str = "Ok";
    }
    else
    {
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
            DbManager::globalManager = new DbManager("109.206.169.214","salary_count",81,"remote","!E3f5c712");
			// test ports: cmd>telnet 109.206.169.214 81
        DbManager::singletonExists = 1;
    }
    return *(DbManager::globalManager);
}
DbManager::~DbManager()
{

}

struct DbConf loadDbConfig()
{
	struct DbConf  dbConf;
	QString fname = "dbconfig.ini";
	QSettings s(fname, QSettings::IniFormat);
	
	if(!QFile::exists(fname))
	{
		//QString hostName, dbName, userName, pass;
		//int port;
		dbConf.hostName = "localhost";
		dbConf.port = 3306;
		dbConf.dbName = "salarycount";
		dbConf.userName = "root";
		dbConf.pass = "root"; // "our366Team";

		// write 
		s.beginGroup("db");
		s.setValue("hostName", dbConf.hostName);
		s.setValue("port", dbConf.port);
		s.setValue("dbName", dbConf.dbName);
		s.setValue("userName", dbConf.userName);
		s.setValue("pass", dbConf.pass);
		s.endGroup();

		// <Debug only>!
		// write "commented" section
		s.beginGroup("db-remote");
		s.setValue("hostName", "109.206.169.214");
		s.setValue("port", dbConf.port);
		s.setValue("dbName", "salary_count");
		s.setValue("userName", "remote");
		s.setValue("pass", "!E3f5c712");
		s.endGroup();
		// </Debug only>

		// write 
		s.beginGroup("meta");
		s.setValue("write_at", QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss"));
		s.endGroup();
	}
	else
	{
		s.beginGroup("db");
		dbConf.hostName = s.value("hostName", "localhost").toString();
		dbConf.port = s.value("port", 3306).toInt();
		dbConf.dbName = s.value("dbName", "salarycount").toString();
		dbConf.userName = s.value("userName", "root").toString();
		dbConf.pass = s.value("pass", "root").toString();
		s.endGroup();

		// read 
		s.beginGroup("meta");
		//s.setValue("write_at", QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss"));
		s.setValue("read_at", QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss"));
		s.endGroup();
	}

	return dbConf;
}