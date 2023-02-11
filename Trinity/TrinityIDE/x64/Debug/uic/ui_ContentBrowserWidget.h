/********************************************************************************
** Form generated from reading UI file 'ContentBrowserWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTENTBROWSERWIDGET_H
#define UI_CONTENTBROWSERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ContentBrowserWidgetClass
{
public:

    void setupUi(QWidget *ContentBrowserWidgetClass)
    {
        if (ContentBrowserWidgetClass->objectName().isEmpty())
            ContentBrowserWidgetClass->setObjectName("ContentBrowserWidgetClass");
        ContentBrowserWidgetClass->resize(600, 400);

        retranslateUi(ContentBrowserWidgetClass);

        QMetaObject::connectSlotsByName(ContentBrowserWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *ContentBrowserWidgetClass)
    {
        ContentBrowserWidgetClass->setWindowTitle(QCoreApplication::translate("ContentBrowserWidgetClass", "ContentBrowserWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ContentBrowserWidgetClass: public Ui_ContentBrowserWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTENTBROWSERWIDGET_H
