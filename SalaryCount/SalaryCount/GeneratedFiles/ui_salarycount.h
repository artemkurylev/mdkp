/********************************************************************************
** Form generated from reading UI file 'salarycount.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SALARYCOUNT_H
#define UI_SALARYCOUNT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SalaryCountClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SalaryCountClass)
    {
        if (SalaryCountClass->objectName().isEmpty())
            SalaryCountClass->setObjectName(QStringLiteral("SalaryCountClass"));
        SalaryCountClass->resize(600, 400);
        menuBar = new QMenuBar(SalaryCountClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        SalaryCountClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SalaryCountClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SalaryCountClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(SalaryCountClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        SalaryCountClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SalaryCountClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SalaryCountClass->setStatusBar(statusBar);

        retranslateUi(SalaryCountClass);

        QMetaObject::connectSlotsByName(SalaryCountClass);
    } // setupUi

    void retranslateUi(QMainWindow *SalaryCountClass)
    {
        SalaryCountClass->setWindowTitle(QApplication::translate("SalaryCountClass", "SalaryCount", 0));
    } // retranslateUi

};

namespace Ui {
    class SalaryCountClass: public Ui_SalaryCountClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SALARYCOUNT_H
