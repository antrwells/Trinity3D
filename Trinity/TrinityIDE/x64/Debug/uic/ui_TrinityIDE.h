/********************************************************************************
** Form generated from reading UI file 'TrinityIDE.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRINITYIDE_H
#define UI_TRINITYIDE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrinityIDEClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TrinityIDEClass)
    {
        if (TrinityIDEClass->objectName().isEmpty())
            TrinityIDEClass->setObjectName("TrinityIDEClass");
        TrinityIDEClass->resize(600, 400);
        menuBar = new QMenuBar(TrinityIDEClass);
        menuBar->setObjectName("menuBar");
        TrinityIDEClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TrinityIDEClass);
        mainToolBar->setObjectName("mainToolBar");
        TrinityIDEClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(TrinityIDEClass);
        centralWidget->setObjectName("centralWidget");
        TrinityIDEClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TrinityIDEClass);
        statusBar->setObjectName("statusBar");
        TrinityIDEClass->setStatusBar(statusBar);

        retranslateUi(TrinityIDEClass);

        QMetaObject::connectSlotsByName(TrinityIDEClass);
    } // setupUi

    void retranslateUi(QMainWindow *TrinityIDEClass)
    {
        TrinityIDEClass->setWindowTitle(QCoreApplication::translate("TrinityIDEClass", "TrinityIDE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TrinityIDEClass: public Ui_TrinityIDEClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRINITYIDE_H
