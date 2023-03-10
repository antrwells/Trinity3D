#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_IsScriptEditor.h"
#include "DockArea.h"
#include <QWidget>

#include "DockManager.h"
#include "qscrollbar.h"

#include "qmenu"
#include <vector>

#include "qmimedata.h"
#include <stack>

class IsScriptEditor : public QMainWindow
{
    Q_OBJECT

public:
    IsScriptEditor(QWidget *parent = nullptr);
    ~IsScriptEditor();
    static IsScriptEditor* mThis;
    void SetStatus(std::string text);
protected:
    void LoadFile();
    void NewFile();

private:
    Ui::IsScriptEditorClass ui;
    DockArea* w_DockArea;
    QMenuBar* menu;
    QMenu* fileMenu;
    QToolBar* toolBar;
    QStatusBar* status;
};
