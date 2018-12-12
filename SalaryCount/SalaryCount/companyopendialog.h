#ifndef COMPANYOPENDIALOG_H
#define COMPANYOPENDIALOG_H

#include <QWidget>
#include "ui_companyopendialog.h"
#include "dbmanager.h"
#include "company.h"
#include "salarycount.h"

class companyOpenDialog : public QDialog
{
    Q_OBJECT

public:
    companyOpenDialog(QWidget *parent = 0);
    ~companyOpenDialog();

private:
    Ui::companyOpenDialog ui;
    void initialDBManager();

private slots:
    void enterCompany();
};

#endif // COMPANYOPENDIALOG_H
