/********************************************************************************
** Form generated from reading UI file 'PropEditor.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPEDITOR_H
#define UI_PROPEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PropEditorClass
{
public:

    void setupUi(QWidget *PropEditorClass)
    {
        if (PropEditorClass->objectName().isEmpty())
            PropEditorClass->setObjectName("PropEditorClass");
        PropEditorClass->resize(600, 400);

        retranslateUi(PropEditorClass);

        QMetaObject::connectSlotsByName(PropEditorClass);
    } // setupUi

    void retranslateUi(QWidget *PropEditorClass)
    {
        PropEditorClass->setWindowTitle(QCoreApplication::translate("PropEditorClass", "PropEditor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropEditorClass: public Ui_PropEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPEDITOR_H
