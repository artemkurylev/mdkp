#ifndef SALARYCOUNT_H
#define SALARYCOUNT_H

#include <QtWidgets/QMainWindow>
#include "ui_salarycount.h"

class SalaryCount : public QMainWindow
{
    Q_OBJECT

public:
    SalaryCount(QWidget *parent = 0);
    ~SalaryCount();

private:
    Ui::SalaryCountClass ui;
};

#endif // SALARYCOUNT_H
