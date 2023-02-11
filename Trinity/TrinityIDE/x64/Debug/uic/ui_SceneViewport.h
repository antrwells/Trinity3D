/********************************************************************************
** Form generated from reading UI file 'SceneViewport.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCENEVIEWPORT_H
#define UI_SCENEVIEWPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SceneViewportClass
{
public:

    void setupUi(QWidget *SceneViewportClass)
    {
        if (SceneViewportClass->objectName().isEmpty())
            SceneViewportClass->setObjectName("SceneViewportClass");
        SceneViewportClass->resize(600, 400);

        retranslateUi(SceneViewportClass);

        QMetaObject::connectSlotsByName(SceneViewportClass);
    } // setupUi

    void retranslateUi(QWidget *SceneViewportClass)
    {
        SceneViewportClass->setWindowTitle(QCoreApplication::translate("SceneViewportClass", "SceneViewport", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SceneViewportClass: public Ui_SceneViewportClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCENEVIEWPORT_H
