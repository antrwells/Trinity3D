/********************************************************************************
** Form generated from reading UI file 'QSceneGraph.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QSCENEGRAPH_H
#define UI_QSCENEGRAPH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QSceneGraphClass
{
public:

    void setupUi(QWidget *QSceneGraphClass)
    {
        if (QSceneGraphClass->objectName().isEmpty())
            QSceneGraphClass->setObjectName("QSceneGraphClass");
        QSceneGraphClass->resize(600, 400);

        retranslateUi(QSceneGraphClass);

        QMetaObject::connectSlotsByName(QSceneGraphClass);
    } // setupUi

    void retranslateUi(QWidget *QSceneGraphClass)
    {
        QSceneGraphClass->setWindowTitle(QCoreApplication::translate("QSceneGraphClass", "QSceneGraph", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QSceneGraphClass: public Ui_QSceneGraphClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QSCENEGRAPH_H
