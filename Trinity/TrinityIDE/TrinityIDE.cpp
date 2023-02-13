#include "TrinityIDE.h"
#include "qpushbutton.h"
#include "qlabel.h"
#include "TrinityGlobal.h"
#include "SceneGraph.h"
#include "DockArea.h"
#include "DockManager.h"
#include "qcombobox.h"
#include "qfile.h"
#include "MonoRT.h"
#include "MonoDLL.h"
#include "ClassMono.h"
#include "ConsoleOutputWidget.h"
#include <vector>

TrinityIDE::TrinityIDE(QWidget *parent)
    : QMainWindow(parent)
{
    //ui.setupUi(this);
    resize(1200, 800);
    menu = menuBar();
    fileMenu = menu->addMenu("Project");

    newProjAction = new QAction("New", this);
    openProjAction = new QAction("Open", this);
    saveProjAction = new QAction("Save", this);
    saveLayoutAction = new QAction("Save State", this);
    loadLayoutAction = new QAction("Load State", this);
    exitAction = new QAction("Exit", this);


    fileMenu->addAction(newProjAction);
    fileMenu->addAction(openProjAction);
    fileMenu->addAction(saveProjAction);
    fileMenu->addSeparator();
    fileMenu->addAction(loadLayoutAction);
    fileMenu->addAction(saveLayoutAction);
    fileMenu->addAction(exitAction);
   

    connect(saveLayoutAction, &QAction::triggered, this, &TrinityIDE::saveLayout);
    connect(loadLayoutAction, &QAction::triggered, this, &TrinityIDE::loadLayout);

    //QPushButton* test = new QPushButton("Test!", this);
    //test->setGeometry(20, 20, 200, 30);

    QImage moveImg("data/ui/moveIcon2.png");
    QImage rotImg("data/ui/rotateIcon.png");
  
    toolBar = addToolBar("My Toolbar");

    QAction* move_act = new QAction(QIcon("data/ui/moveIcon2.png"), "Translate Mode", this);
    move_act->setShortcut(QKeySequence("F1"));
    toolBar->addAction(move_act);

    QAction* rot_act = new QAction(QIcon("data/ui/rotateIcon.png"), "Rotate Mode", this);
    rot_act->setShortcut(QKeySequence("F2"));
    toolBar->addAction(rot_act);

    QAction* scale_act = new QAction(QIcon("edit/icon/scaleIcon.png"), "Scale Mode", this);
    scale_act->setShortcut(QKeySequence("F3"));

    toolBar->addAction(scale_act);

    toolBar->addSeparator();
    toolBar->addSeparator();

    QComboBox* localeBox = new QComboBox(this);
    localeBox->addItem("Local");
    localeBox->addItem("Global");

    QLabel* label = new QLabel("Edit Space:   ", this);
     
    toolBar->addWidget(label);

    toolBar->addWidget(localeBox);

    localeBox->setCurrentIndex(1);

    connect(localeBox, &QComboBox::currentIndexChanged, this, &TrinityIDE::act_LocalSpace);


    connect(move_act, &QAction::triggered, this, &TrinityIDE::act_move);
    connect(rot_act, &QAction::triggered, this, &TrinityIDE::act_rotate);
    connect(scale_act, &QAction::triggered, this, &TrinityIDE::act_scale);
    /*
    w_Toolbar = new ToolBarWidget(this);
    w_Toolbar->setGeometry(QRect(0, 26, width(), 60));

    QImage moveImg("data/ui/moveIcon2.png");
    QImage rotImg("data/ui/rotateIcon.png");

    auto move_act = [&]()
    {
        w_DockArea->SetViewportMode(0);
    };

    auto rotate_act = [&]() {
        w_DockArea->SetViewportMode(1);
    };


    w_Toolbar->AddImageButton(moveImg,move_act);
    w_Toolbar->AddImageButton(rotImg, rotate_act);
    */

    mProjectPath = "c:\\content\\";

    w_DockArea = new DockArea(this);
    w_DockArea->setGeometry(0, 26+34, width(), height() -(26+34));

    auto dll_path = mProjectPath + std::string("gamenet.dll");

  

    return;


    //connect(this, &SceneViewport::ViewportReady, this, &TrinityIDE::ViewportReady)


    /*
    QLabel* l = new QLabel();
    l->setWordWrap(true);
    l->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    l->setText("Lorem ipsum dolor sit amet, consectetuer adipiscing elit. ");

    // Create a dock widget with the title Label 1 and set the created label
    // as the dock widget content
    ads::CDockWidget* DockWidget = new ads::CDockWidget("Label 1");
    DockWidget->setWidget(l);
    // Add the dock widget to the top dock widget area
    m_DockManager->addDockWidget(ads::TopDockWidgetArea, DockWidget);

    QLabel* l2 = new QLabel();
    l2->setWordWrap(true);
    l2->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    l2->setText("This is label 2!!!!!!!!!!!!!!!");
    ads::CDockWidget* DockWidget2 = new ads::CDockWidget("Label 2");
    DockWidget2->setWidget(l2);
    m_DockManager->addDockWidget(ads::BottomDockWidgetArea, DockWidget2);
    */
}

void TrinityIDE::ViewportReady() {

    int aa = 5;

}

void TrinityIDE::resizeEvent(QResizeEvent* event) {

    //w_Toolbar->resize(width(), 60);
    //w_DockArea->setGeometry(0, 26+60, width(), height() - 86);
    w_DockArea->resize(width(), height() - 60);

    //m_DockManager->setGeometry(0, 60, width(), height() - 60);

    // Handle the resize event here
    QMainWindow::resizeEvent(event);

}

TrinityIDE::~TrinityIDE()
{}


void TrinityIDE::act_move() {
    w_DockArea->SetViewportMode(0);
}

void TrinityIDE::act_rotate()
{
    w_DockArea->SetViewportMode(1);
}

void TrinityIDE::act_scale() {
    w_DockArea->SetViewportMode(2);
}

void TrinityIDE::act_LocalSpace(int id) {

    w_DockArea->SetViewportLocalMode(id);

}

void TrinityIDE::loadLayout() {

    w_DockArea->LoadState("layout/ads.state");

}

void TrinityIDE::saveLayout() {


    w_DockArea->SaveState("layout/ads.state");

    return;
    
    QByteArray data = saveState();

    QFile file("layout/layout.dat");
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream stream(&file);
        stream << data;
        file.close();
    }

}