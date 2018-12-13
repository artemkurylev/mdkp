#ifndef SALARYCOUNTPROFILE_H
#define SALARYCOUNTPROFILE_H

#include <delegateStates>

class SalaryCountProfile : public delegateStates
{
    Q_OBJECT

public:
    SalaryCountProfile(QObject *parent);
    ~SalaryCountProfile();
    

private:
    Ui_SalaryCount *ui;//не самый при€тный способ, зато все видно из коробки


};

#endif // SALARYCOUNTPROFILE_H
