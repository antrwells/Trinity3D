/********************************************************************************
** Form generated from reading UI file 'MaterialEditorWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATERIALEDITORWIDGET_H
#define UI_MATERIALEDITORWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MaterialEditorWidgetClass
{
public:

    void setupUi(QWidget *MaterialEditorWidgetClass)
    {
        if (MaterialEditorWidgetClass->objectName().isEmpty())
            MaterialEditorWidgetClass->setObjectName("MaterialEditorWidgetClass");
        MaterialEditorWidgetClass->resize(600, 400);

        retranslateUi(MaterialEditorWidgetClass);

        QMetaObject::connectSlotsByName(MaterialEditorWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *MaterialEditorWidgetClass)
    {
        MaterialEditorWidgetClass->setWindowTitle(QCoreApplication::translate("MaterialEditorWidgetClass", "MaterialEditorWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MaterialEditorWidgetClass: public Ui_MaterialEditorWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATERIALEDITORWIDGET_H
