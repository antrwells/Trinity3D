#include "TrinityIDE.h"
#include "qpushbutton.h"
#include "qlabel.h"
#include "TrinityGlobal.h"
#include "SceneGraph.h"
#include "DockAreaWidget.h"


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
    exitAction = new QAction("Exit", this);

    fileMenu->addAction(newProjAction);
    fileMenu->addAction(openProjAction);
    fileMenu->addAction(saveProjAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
   
    //QPushButton* test = new QPushButton("Test!", this);
    //test->setGeometry(20, 20, 200, 30);

    w_Toolbar = new ToolBarWidget(this);
    w_Toolbar->setGeometry(QRect(0, 26, width(), 60));

    QImage moveImg("data/ui/moveIcon2.png");
    QImage rotImg("data/ui/rotateIcon.png");

    w_Toolbar->AddImageButton(moveImg);
    w_Toolbar->AddImageButton(rotImg);


    w_DockArea = new DockAreaWidget(this);
    w_DockArea->setGeometry(0, 26+60, width(), height() - 56);

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

    w_Toolbar->resize(width(), 60);
    w_DockArea->setGeometry(0, 26+60, width(), height() - 86);

    //m_DockManager->setGeometry(0, 60, width(), height() - 60);

    // Handle the resize event here
    QMainWindow::resizeEvent(event);

}

TrinityIDE::~TrinityIDE()
{}
