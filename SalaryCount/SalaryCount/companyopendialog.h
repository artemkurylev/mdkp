#ifndef COMPANYOPENDIALOG_H
#define COMPANYOPENDIALOG_H

#include <QWidget>
#include "ui_companyopendialog.h"
#include "dbmanager.h"
#include "company.h"
#include "salarycount.h"
#include "companycreationdialog.h"
#include "log_errors.h"
#include "employeesc.h"

class companyOpenDialog : public QDialog
{
    Q_OBJECT

public:
    companyOpenDialog(QWidget *parent = 0);
    ~companyOpenDialog();//xyi

private:
    Ui::companyOpenDialog ui;
    void initialDBManager();
    void updateCompanyList();

	void error_msg(const char* short_description, const char* text);

	log_errors* journal;


private slots:
    void enterCompany();
    void createCompany();
	void enterEmployee();
};

#endif // COMPANYOPENDIALOG_H
