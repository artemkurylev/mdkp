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
/*static*/bool DbManager::singletonCompanyExists = false;
/*static*/DbManager* DbManager::globalManager = 0;
/*static*/DbManager* DbManager::_companyManager = 0;
DbManager::DbManager(const QString& hostName, const QString& dbName, int port,const QString& userName, const QString& pass)
{
	// Сначала создаём БД
    this->db = QSqlDatabase::addDatabase("QMYSQL");
    //this->companyDb = QSqlDatabase::addDatabase("QMYSQL");
    this->db.setUserName(userName);
    //this->db.setDatabaseName(dbName);
    this->db.setHostName(hostName);
    this->db.setPort(port);
    this->db.setPassword(pass);

    if(this->db.open())
    {
        //QString str;
		QSqlQuery q(this->db);
		if( q.exec(tr("CREATE DATABASE IF NOT EXISTS %1 CHARACTER SET utf8 COLLATE utf8_bin;").arg(dbName) ) )
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
		// проверка активности соединения
		// источник: http://www.prog.org.ru/topic_6693_0.html Russian Qt Forum >> Базы данных > Lost connection to MySQL server during query QMYSQL: Unable to execute query
		QSqlQuery qq = db.exec("SET NAMES 'utf8'");
		if (qq.lastError().type()!=QSqlError::NoError)
		{
			db.close();
			db.open();
		}

        return db.isOpen();
    }
    else
    {
        QString s= db.lastError().text();
        return false;
    }
}
/*static*/ DbManager& DbManager::companyManager()
{
    if(!singletonCompanyExists)
    {
        struct DbConf conf = loadDbConfig();
		//QString hostName, dbName, userName, pass;
		//int port;
        DbManager::_companyManager = new DbManager(conf.hostName,conf.dbName,conf.port,conf.userName,conf.pass);
        //if(false)
        //    DbManager::globalManager = new DbManager("localhost","salarycount",3306,"root","root");
        //else
        //    DbManager::globalManager = new DbManager("109.206.169.214","salary_count",443,"remote","!E3f5c712");
		// test ports: cmd>telnet 109.206.169.214 81
        DbManager::singletonCompanyExists = 1;
    }
    return *(DbManager::_companyManager);
}
/*static*/ DbManager& DbManager::manager()
{
    if(!singletonExists)
    {
		struct DbConf conf = loadDbConfig();
		//QString hostName, dbName, userName, pass;
		//int port;
		DbManager::globalManager = new DbManager(conf.hostName,conf.dbName,conf.port,conf.userName,conf.pass);
        //if(false)
        //    DbManager::globalManager = new DbManager("localhost","salarycount",3306,"root","root");
        //else
        //    DbManager::globalManager = new DbManager("109.206.169.214","salary_count",443,"remote","!E3f5c712");
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
		s.beginGroup("db-local");
		s.setValue("hostName", dbConf.hostName);
		s.setValue("port", dbConf.port);
		s.setValue("dbName", dbConf.dbName);
		s.setValue("userName", dbConf.userName);
		s.setValue("pass", dbConf.pass);
		s.endGroup();

		// <Debug only>!
		// write "commented" section
		s.beginGroup("db");
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