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
    Ui_SalaryCount *ui;//�� ����� �������� ������, ���� ��� ����� �� �������


};

#endif // SALARYCOUNTPROFILE_H
