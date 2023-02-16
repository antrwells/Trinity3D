/********************************************************************************
** Form generated from reading UI file 'ImportMediaForm.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMPORTMEDIAFORM_H
#define UI_IMPORTMEDIAFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImportMediaFormClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ImportMediaFormClass)
    {
        if (ImportMediaFormClass->objectName().isEmpty())
            ImportMediaFormClass->setObjectName("ImportMediaFormClass");
        ImportMediaFormClass->resize(600, 400);
        menuBar = new QMenuBar(ImportMediaFormClass);
        menuBar->setObjectName("menuBar");
        ImportMediaFormClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ImportMediaFormClass);
        mainToolBar->setObjectName("mainToolBar");
        ImportMediaFormClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ImportMediaFormClass);
        centralWidget->setObjectName("centralWidget");
        ImportMediaFormClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ImportMediaFormClass);
        statusBar->setObjectName("statusBar");
        ImportMediaFormClass->setStatusBar(statusBar);

        retranslateUi(ImportMediaFormClass);

        QMetaObject::connectSlotsByName(ImportMediaFormClass);
    } // setupUi

    void retranslateUi(QMainWindow *ImportMediaFormClass)
    {
        ImportMediaFormClass->setWindowTitle(QCoreApplication::translate("ImportMediaFormClass", "ImportMediaForm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImportMediaFormClass: public Ui_ImportMediaFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPORTMEDIAFORM_H
