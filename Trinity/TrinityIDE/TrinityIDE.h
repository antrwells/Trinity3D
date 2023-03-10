#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TrinityIDE.h"
#include "DockManager.h"

#include "ToolBarWidget.h"
#include "DockArea.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "ScriptObject.h"

class TrinityIDE : public QMainWindow
{
    Q_OBJECT

public:
    TrinityIDE(QWidget *parent = nullptr);
    ~TrinityIDE();
    TrinityIDE* GetWindow() {
        return mThis;
    }

private slots:
    void ViewportReady();
    void act_move();
    void act_rotate();
    void act_scale();
    void act_LocalSpace(int id);
    void act_play();
    void act_pause();
    void act_stop();
    void saveScene();
    void loadScene();

//create primitives
    void create_plane();
    void create_box();
    void create_sphere();
    void create_cylinder();
    void create_cone();
    void create_torus();
//create lights
    void create_pointlight();
    void create_spotlight();
    void create_dirlight();


protected:
    void resizeEvent(QResizeEvent* event) override;
public:
    static TrinityIDE* mThis;


private:
    QMenuBar* menu;
    QMenu* fileMenu;
    QAction* newProjAction;
    QAction* openProjAction;
    QAction* saveProjAction;
    QAction* exitAction;
    QAction* saveSceneAction;
    QAction* loadSceneAction;
    std::string mProjectPath;
    ToolBarWidget* w_Toolbar;
    DockArea* w_DockArea;
    QToolBar* toolBar;
    Ui::TrinityIDEClass ui;
    ScriptContainer* s_IDE;

};
