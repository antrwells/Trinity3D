#include "IsScriptEditor.h"
#include <QFileDialog>
#include "qfileinfo.h"

IsScriptEditor::IsScriptEditor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    resize(1200, 800);
    menu = menuBar();
    fileMenu = menu->addMenu("File");

    auto load_file = new QAction("Load Script");

    fileMenu->addAction(load_file);

    connect(load_file, &QAction::triggered, this, &IsScriptEditor::LoadFile);


    toolBar = addToolBar("My Toolbar");
    w_DockArea = new DockArea(this);
    w_DockArea->setGeometry(0, 26 + 34, width(), height() - (26 + 34));

    //w_DockArea->AddNewPage();


    QAction* act_test = new QAction("Test Script", this);
    act_test->setShortcut(QKeySequence("F1"));
    toolBar->addAction(act_test);


}

IsScriptEditor::~IsScriptEditor()
{}


void IsScriptEditor::LoadFile() {

    QString fileName = QFileDialog::getOpenFileName(this, "Open Script", "", "Is Scripts (*.zs);;All Files (*)");
    if (!fileName.isEmpty()) {

        QFileInfo fileInfo(fileName);
        QString fileExtension = fileInfo.suffix();

        auto ss = fileExtension.toStdString();

        if (ss == std::string("zs")) {

            w_DockArea->LoadScript(fileName.toStdString());
            //Import3DForm* form = new Import3DForm;
           // form->SetPath(fileInfo.filePath().toStdString());
           // form->show();
        }
    }

}