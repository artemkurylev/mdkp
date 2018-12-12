#ifndef COMPANYCREATIONDIALOG_H
#define COMPANYCREATIONDIALOG_H

#include <QDialog>
#include "ui_companycreationdialog.h"

class companyCreationDialog : public QDialog
{
    Q_OBJECT

public:
    companyCreationDialog(QWidget *parent = 0);
    ~companyCreationDialog();

private:
    Ui::companyCreationDialog ui;
};

#endif // COMPANYCREATIONDIALOG_H
