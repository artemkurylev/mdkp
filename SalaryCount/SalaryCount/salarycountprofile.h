#ifndef SALARYCOUNTPROFILE_H
#define SALARYCOUNTPROFILE_H

#include "delegateStates.h"
#include "employee.h"
#include"company.h"

class SalaryCountProfile : public delegateStates
{
    Q_OBJECT

public:
    SalaryCountProfile(Ui_SalaryCount *ui, QString name="");
    ~SalaryCountProfile();
    

private:
    Ui_SalaryCount *ui;//�� ����� �������� ������, ���� ��� ����� �� �������

public slots:
	void updateInfo(QString name);
	void startCompany();
};

#endif // SALARYCOUNTPROFILE_H
