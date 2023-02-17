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

private slots:
    void ViewportReady();
    void act_move();
    void act_rotate();
    void act_scale();
    void act_LocalSpace(int id);
    void act_play();
    void act_pause();
    void act_stop();
    void saveLayout();
    void loadLayout();

//create primitives
    void create_plane();
    void create_box();
    void create_sphere();
    void create_cylinder();
    void create_cone();
    void create_torus();



protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    QMenuBar* menu;
    QMenu* fileMenu;
    QAction* newProjAction;
    QAction* openProjAction;
    QAction* saveProjAction;
    QAction* exitAction;
    QAction* saveLayoutAction;
    QAction* loadLayoutAction;
    std::string mProjectPath;
    ToolBarWidget* w_Toolbar;
    DockArea* w_DockArea;
    QToolBar* toolBar;
    Ui::TrinityIDEClass ui;
    ScriptContainer* s_IDE;

};
