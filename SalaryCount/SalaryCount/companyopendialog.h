#ifndef COMPANYOPENDIALOG_H
#define COMPANYOPENDIALOG_H

#include <QWidget>
#include "ui_companyopendialog.h"
#include "dbmanager.h"
#include "company.h"

class companyOpenDialog : public QDialog
{
    Q_OBJECT

public:
    companyOpenDialog(QWidget *parent = 0);
    ~companyOpenDialog();

private:
    Ui::companyOpenDialog ui;
    void initialDBManager();
};

#endif // COMPANYOPENDIALOG_H
