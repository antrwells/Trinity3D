/********************************************************************************
** Form generated from reading UI file 'DirectXHost.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIRECTXHOST_H
#define UI_DIRECTXHOST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DirectXHostClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DirectXHostClass)
    {
        if (DirectXHostClass->objectName().isEmpty())
            DirectXHostClass->setObjectName("DirectXHostClass");
        DirectXHostClass->resize(600, 400);
        menuBar = new QMenuBar(DirectXHostClass);
        menuBar->setObjectName("menuBar");
        DirectXHostClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DirectXHostClass);
        mainToolBar->setObjectName("mainToolBar");
        DirectXHostClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(DirectXHostClass);
        centralWidget->setObjectName("centralWidget");
        DirectXHostClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(DirectXHostClass);
        statusBar->setObjectName("statusBar");
        DirectXHostClass->setStatusBar(statusBar);

        retranslateUi(DirectXHostClass);

        QMetaObject::connectSlotsByName(DirectXHostClass);
    } // setupUi

    void retranslateUi(QMainWindow *DirectXHostClass)
    {
        DirectXHostClass->setWindowTitle(QCoreApplication::translate("DirectXHostClass", "DirectXHost", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DirectXHostClass: public Ui_DirectXHostClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIRECTXHOST_H
