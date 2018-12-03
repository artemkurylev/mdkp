#ifndef COMPANY_H
#define COMPANY_H

#include "dbrecord.h"

class Company : public DbRecord
{
    Q_OBJECT

public:
    Company(QObject *parent = 0);
    ~Company();

private:
    
};

#endif // COMPANY_H
