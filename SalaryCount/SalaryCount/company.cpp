#include "company.h"
#include <QCryptographicHash>
#include <qbytearray.h>

Company* Company::currentCompany = NULL;

Company::Company(QObject *parent)
    : DbRecord(0)
{

}
int Company::insert()
{
    int insert_id = -1;
    if(DbManager::companyManager().checkConnection())
    {
        QSqlQuery* query = DbManager::companyManager().makeQuery();
        query->prepare("INSERT INTO `company` (`name`,`pass`,`creation_date`) VALUES(:name,:pass,:date)");
        
        QByteArray hash;
        hash.append(this->_pass);
        QString hsh = QCryptographicHash::hash(hash,QCryptographicHash::Md5);
        query->bindValue(":name",this->_name);
        query->bindValue(":pass",hsh);
        query->bindValue(":date",this->_creationDate);
        if(query->exec())
        {
            if(query->exec("SELECT LAST_INSERT_ID()") && query->next())
            {   
                this->_id = query->value(0).toInt();
				insert_id = this->_id;
            }
        }
        else
        {
            QString s = query->lastError().text();
            s+="as";
        }
        delete query;
    }
    else{
    }
	return insert_id;
}
bool Company::createTable()
{
    bool success = false;
    if(DbManager::companyManager().checkConnection())
    {
        QSqlQuery* query = DbManager::companyManager().makeQuery();
        if(query->exec("CREATE TABLE IF NOT EXISTS `company` (`id` INT(11) NOT NULL AUTO_INCREMENT, `name` VARCHAR(30) UNIQUE, `pass` VARCHAR(200) , `creation_date` DATE ,PRIMARY KEY(`id`))"))
		{
            success = true;
		}
        else
        {
            QString s = query->lastError().text();
            s+="as";
        }
        delete query;
    }
    else
    {
    }
    return success;
}
bool Company::validate() const
{
    bool success = true;
    QSqlQuery* query = DbManager::companyManager().makeQuery();
    query->prepare("SELECT * FROM `company` WHERE `name` = :name");
    query->bindValue(":name",this->_name);
    if(DbManager::companyManager().checkConnection())
    {
        if(query->exec())
        {
            if(query->next())
            {
                success = false;
            }
        }
    }

	QString canMakeNewDb("SHOW DATABASES LIKE \"%1\"");
	if(query->exec(canMakeNewDb.arg(this->_name)) && query->next())
    {   
        //int conflict = query->value(0).toInt();
		//if(conflict)
            success = false;
    }

    return success;
}
bool Company::auth()
{
    bool success = false;
    QByteArray hash;
    hash.append(this->_pass);
    QString hsh = QCryptographicHash::hash(hash,QCryptographicHash::Md5);
    QSqlQuery* query = DbManager::companyManager().makeQuery();
    query->prepare("SELECT * FROM `company` WHERE `name` = :name");
    query->bindValue(":name",this->_name);
    if(DbManager::companyManager().checkConnection())
    {
        if(query->exec())
        {
            if(query->next())
            {
                QString pass = query->value(2).toString();
                if(pass == hsh)
                {
                    success = true;
                }
            }
        }
        else
        {
            QString s= query->lastError().text();
            s+= "as";
        }
    }
    return success;
}
int Company::countEntries(){
    int counter = 0;
    if(DbManager::companyManager().checkConnection())
    {
        QSqlQuery* query = DbManager::companyManager().makeQuery();

        query->prepare("SELECT COUNT(*) FROM `company`");
        if(query->exec())
        {
            if(query->next())
                counter = query->value(0).toInt();
        }       
        delete query;
    }
    return counter;
}
QMap<int,QString> Company::getAll(){
    QMap<int,QString> records;
    if(DbManager::companyManager().checkConnection())
    {
        QSqlQuery* query = DbManager::companyManager().makeQuery();

        query->prepare("SELECT `id`,`name` FROM `company`");
        if(query->exec())
        {
            while(query->next())
            {
                records.insert(query->value(0).toInt(), query->value(1).toString()); 
            }
        }
        delete query;
    }

    return records;
}
Company::~Company()
{

}

void initializeCompany(){
    QString name = "test";
    QString pass = "test";
    Company company(name,pass);
    company.insert();

}