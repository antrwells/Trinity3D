#include "TrinityIDE.h"
#include "qpushbutton.h"
#include "qlabel.h"


TrinityIDE::TrinityIDE(QWidget *parent)
    : QMainWindow(parent)
{
    //ui.setupUi(this);
    resize(800, 600);

    m_DockManager = new ads::CDockManager(this);

    //QPushButton* test = new QPushButton("Test!", this);
    //test->setGeometry(20, 20, 200, 30);

    w_SceneGraph = new QSceneGraph(NULL);
    m_DockManager->addDockWidget(ads::LeftDockWidgetArea,w_SceneGraph);

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

TrinityIDE::~TrinityIDE()
{}
