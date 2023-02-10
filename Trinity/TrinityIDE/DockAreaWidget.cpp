#include "DockAreaWidget.h"

DockAreaWidget::DockAreaWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_DockManager = new ads::CDockManager(this);
	m_DockManager->setGeometry(0, 0, width(), height());


	w_SceneView = new SceneViewport(NULL);
	//   connect(this, &SceneViewport::ViewportReady, this, &TrinityIDE::ViewportReady);
	m_DockManager->addDockWidget(ads::CenterDockWidgetArea, w_SceneView);

	w_SceneGraph = new QSceneGraph(NULL);
	m_DockManager->addDockWidget(ads::LeftDockWidgetArea, w_SceneGraph);

}

DockAreaWidget::~DockAreaWidget()
{}

void DockAreaWidget::resizeEvent(QResizeEvent* event) {

	m_DockManager->setGeometry(0, 0, width(), height());

}