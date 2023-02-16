/********************************************************************************
** Form generated from reading UI file 'PropEditorSurface.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPEDITORSURFACE_H
#define UI_PROPEDITORSURFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PropEditorSurfaceClass
{
public:

    void setupUi(QWidget *PropEditorSurfaceClass)
    {
        if (PropEditorSurfaceClass->objectName().isEmpty())
            PropEditorSurfaceClass->setObjectName("PropEditorSurfaceClass");
        PropEditorSurfaceClass->resize(600, 400);

        retranslateUi(PropEditorSurfaceClass);

        QMetaObject::connectSlotsByName(PropEditorSurfaceClass);
    } // setupUi

    void retranslateUi(QWidget *PropEditorSurfaceClass)
    {
        PropEditorSurfaceClass->setWindowTitle(QCoreApplication::translate("PropEditorSurfaceClass", "PropEditorSurface", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropEditorSurfaceClass: public Ui_PropEditorSurfaceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPEDITORSURFACE_H
