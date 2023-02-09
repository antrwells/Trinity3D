#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TrinityIDE.h"
#include "DockManager.h"
#include "QSceneGraph.h"

class TrinityIDE : public QMainWindow
{
    Q_OBJECT

public:
    TrinityIDE(QWidget *parent = nullptr);
    ~TrinityIDE();

private:

    ads::CDockManager* m_DockManager;
    
    QSceneGraph* w_SceneGraph;

    Ui::TrinityIDEClass ui;
};
