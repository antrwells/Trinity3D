/********************************************************************************
** Form generated from reading UI file 'DockAreaWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCKAREAWIDGET_H
#define UI_DOCKAREAWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DockAreaWidgetClass
{
public:

    void setupUi(QWidget *DockAreaWidgetClass)
    {
        if (DockAreaWidgetClass->objectName().isEmpty())
            DockAreaWidgetClass->setObjectName("DockAreaWidgetClass");
        DockAreaWidgetClass->resize(600, 400);

        retranslateUi(DockAreaWidgetClass);

        QMetaObject::connectSlotsByName(DockAreaWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *DockAreaWidgetClass)
    {
        DockAreaWidgetClass->setWindowTitle(QCoreApplication::translate("DockAreaWidgetClass", "DockAreaWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DockAreaWidgetClass: public Ui_DockAreaWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCKAREAWIDGET_H
