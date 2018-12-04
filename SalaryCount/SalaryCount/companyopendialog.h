#ifndef COMPANYOPENDIALOG_H
#define COMPANYOPENDIALOG_H

#include <QWidget>
#include "ui_companyopendialog.h"

class companyOpenDialog : public QDialog
{
    Q_OBJECT

public:
    companyOpenDialog(QWidget *parent = 0);
    ~companyOpenDialog();

private:
    Ui::companyOpenDialog ui;
};

#endif // COMPANYOPENDIALOG_H
