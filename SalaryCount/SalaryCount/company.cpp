#include "company.h"
#include <QCryptographicHash>
#include <qbytearray.h>
Company::Company(QObject *parent)
    : DbRecord(0)
{

}
bool Company::createTable()
{
    bool success = false;
    if(DbManager::manager().checkConnection())
    {
        QSqlQuery* query = DbManager::manager().makeQuery();
        if(query->exec("CREATE TABLE IF NOT EXISTS `company` (`id` INT(11) NOT NULL AUTO_INCREMENT, `name` VARCHAR(30) UNIQUE, `pass` VARCHAR(200)"))
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
bool Company::auth()
{
    bool success = false;
    QByteArray hash;
    hash.append(this->_pass);
    QString hsh = QCryptographicHash::hash(hash,QCryptographicHash::Md5);
    QSqlQuery* query = DbManager::manager().makeQuery();
    if(DbManager::manager().checkConnection())
    {
        if(query->exec("SELECT * FROM `company` WHERE `name` == :name"))
        {
            if(query->next())
            {
                QString pass = query->value(2).toString();
                if(pass == hash)
                {
                    success = true;
                }
            }

        }
    }

    return success;
}
Company::~Company()
{

}
