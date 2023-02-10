#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TrinityIDE.h"
#include "DockManager.h"
#include "QSceneGraph.h"
#include "SceneViewport.h"

class TrinityIDE : public QMainWindow
{
    Q_OBJECT

public:
    TrinityIDE(QWidget *parent = nullptr);
    ~TrinityIDE();

private slots:
    void ViewportReady();

private:

    ads::CDockManager* m_DockManager;
    
    QSceneGraph* w_SceneGraph;
    SceneViewport* w_SceneView;

    Ui::TrinityIDEClass ui;
};
