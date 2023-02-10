#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TrinityIDE.h"
#include "DockManager.h"

#include "ToolBarWidget.h"
#include "DockAreaWidget.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
class TrinityIDE : public QMainWindow
{
    Q_OBJECT

public:
    TrinityIDE(QWidget *parent = nullptr);
    ~TrinityIDE();

private slots:
    void ViewportReady();

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    QMenuBar* menu;
    QMenu* fileMenu;
    QAction* newProjAction;
    QAction* openProjAction;
    QAction* saveProjAction;
    QAction* exitAction;
  
    ToolBarWidget* w_Toolbar;
    DockAreaWidget* w_DockArea;

    Ui::TrinityIDEClass ui;
};
