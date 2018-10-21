#ifndef MARK_H
#define MARK_H

#include "dbrecord.h"

class Mark : public DbRecord
{
    Q_OBJECT

public:
    Mark(QObject *parent);
    ~Mark();

private:
    int base;
    int altered;
};

#endif // MARK_H
