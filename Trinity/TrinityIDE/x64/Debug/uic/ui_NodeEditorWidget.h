/********************************************************************************
** Form generated from reading UI file 'NodeEditorWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NODEEDITORWIDGET_H
#define UI_NODEEDITORWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NodeEditorWidgetClass
{
public:

    void setupUi(QWidget *NodeEditorWidgetClass)
    {
        if (NodeEditorWidgetClass->objectName().isEmpty())
            NodeEditorWidgetClass->setObjectName("NodeEditorWidgetClass");
        NodeEditorWidgetClass->resize(600, 400);

        retranslateUi(NodeEditorWidgetClass);

        QMetaObject::connectSlotsByName(NodeEditorWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *NodeEditorWidgetClass)
    {
        NodeEditorWidgetClass->setWindowTitle(QCoreApplication::translate("NodeEditorWidgetClass", "NodeEditorWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NodeEditorWidgetClass: public Ui_NodeEditorWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NODEEDITORWIDGET_H
