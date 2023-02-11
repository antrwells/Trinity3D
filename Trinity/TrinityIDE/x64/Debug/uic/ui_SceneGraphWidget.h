/********************************************************************************
** Form generated from reading UI file 'SceneGraphWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCENEGRAPHWIDGET_H
#define UI_SCENEGRAPHWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SceneGraphWidgetClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SceneGraphWidgetClass)
    {
        if (SceneGraphWidgetClass->objectName().isEmpty())
            SceneGraphWidgetClass->setObjectName("SceneGraphWidgetClass");
        SceneGraphWidgetClass->resize(600, 400);
        menuBar = new QMenuBar(SceneGraphWidgetClass);
        menuBar->setObjectName("menuBar");
        SceneGraphWidgetClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SceneGraphWidgetClass);
        mainToolBar->setObjectName("mainToolBar");
        SceneGraphWidgetClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(SceneGraphWidgetClass);
        centralWidget->setObjectName("centralWidget");
        SceneGraphWidgetClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SceneGraphWidgetClass);
        statusBar->setObjectName("statusBar");
        SceneGraphWidgetClass->setStatusBar(statusBar);

        retranslateUi(SceneGraphWidgetClass);

        QMetaObject::connectSlotsByName(SceneGraphWidgetClass);
    } // setupUi

    void retranslateUi(QMainWindow *SceneGraphWidgetClass)
    {
        SceneGraphWidgetClass->setWindowTitle(QCoreApplication::translate("SceneGraphWidgetClass", "SceneGraphWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SceneGraphWidgetClass: public Ui_SceneGraphWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCENEGRAPHWIDGET_H
