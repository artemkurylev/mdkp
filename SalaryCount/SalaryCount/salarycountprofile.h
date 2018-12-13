#ifndef SALARYCOUNTPROFILE_H
#define SALARYCOUNTPROFILE_H

#include "delegateStates.h"


class SalaryCountProfile : public delegateStates
{
    Q_OBJECT

public:
    SalaryCountProfile(Ui_SalaryCount *ui, QString name="");
    ~SalaryCountProfile();
    

private:
    Ui_SalaryCount *ui;//не самый при€тный способ, зато все видно из коробки

public slots:
	void updateInfo(QString name);
};

#endif // SALARYCOUNTPROFILE_H
