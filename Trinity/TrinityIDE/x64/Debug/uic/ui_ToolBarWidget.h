/********************************************************************************
** Form generated from reading UI file 'ToolBarWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLBARWIDGET_H
#define UI_TOOLBARWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ToolBarWidgetClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ToolBarWidgetClass)
    {
        if (ToolBarWidgetClass->objectName().isEmpty())
            ToolBarWidgetClass->setObjectName("ToolBarWidgetClass");
        ToolBarWidgetClass->resize(600, 400);
        menuBar = new QMenuBar(ToolBarWidgetClass);
        menuBar->setObjectName("menuBar");
        ToolBarWidgetClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ToolBarWidgetClass);
        mainToolBar->setObjectName("mainToolBar");
        ToolBarWidgetClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ToolBarWidgetClass);
        centralWidget->setObjectName("centralWidget");
        ToolBarWidgetClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ToolBarWidgetClass);
        statusBar->setObjectName("statusBar");
        ToolBarWidgetClass->setStatusBar(statusBar);

        retranslateUi(ToolBarWidgetClass);

        QMetaObject::connectSlotsByName(ToolBarWidgetClass);
    } // setupUi

    void retranslateUi(QMainWindow *ToolBarWidgetClass)
    {
        ToolBarWidgetClass->setWindowTitle(QCoreApplication::translate("ToolBarWidgetClass", "ToolBarWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ToolBarWidgetClass: public Ui_ToolBarWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLBARWIDGET_H
