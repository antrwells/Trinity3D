#include "DockArea.h"
#include "TrinityGlobal.h"
#include <QDockWidget>
//#include <QtAdvancedDockingSystem/QtAdvancedDockingSystem>
#include "DockManager.h"
#include "DockAreaWidget.h"
#include "VFile.h"
#include "qsplitter.h"
#include "qfile.h"

DockArea::DockArea(QWidget *parent)
	: QWidget(parent)
	, settings("Vivid","Trinity")
{
	ui.setupUi(this);

	

	m_DockManager = new ads::CDockManager(this);
	m_DockManager->setGeometry(0, 0, width(), height());


	w_SceneView = new SceneViewport(NULL);

	
	//   connect(this, &SceneViewport::ViewportReady, this, &TrinityIDE::ViewportReady);
	auto w1 = m_DockManager->addDockWidget(ads::CenterDockWidgetArea, w_SceneView);

	w_SceneGraph = new QSceneGraph(NULL);
	
	//w_SceneGraph->resize(50, w_SceneGraph->height());
	//w_SceneGraph->setFixedWidth(50);

	w_NodeEditor = new NodeEditorWidget(NULL);
	auto w4 = m_DockManager->addDockWidget(ads::RightDockWidgetArea, w_NodeEditor);

	auto w2 = m_DockManager->addDockWidget(ads::LeftDockWidgetArea, w_SceneGraph);
	w_ContentBrowser = new ContentBrowserWidget(NULL);
	auto w3 = m_DockManager->addDockWidget(ads::BottomDockWidgetArea, w_ContentBrowser);
//	w3->setMaximumHeight(150);

	w_Console = new ConsoleOutputWidget(NULL);
	auto w5 = m_DockManager->addDockWidgetTabToArea(w_Console,w3) ;// ddDockWidget(ads::BottomDockWidgetArea, w_Console);






	QSplitter* splitter = qobject_cast<QSplitter*>(w1->parentWidget());
	QList<int> splitterSizes;
	splitterSizes << 150 << width() - 300 << 200;
	splitter->setSizes(splitterSizes);


	w_ContentBrowser->Browse("c:\\content\\");
	


}

DockArea::~DockArea()
{}

void DockArea::resizeEvent(QResizeEvent* event) {

	m_DockManager->setGeometry(0, 0, width(), height());

	if (TrinityGlobal::CurrentScene != nullptr) {
		auto cam = TrinityGlobal::CurrentScene->GetCamera();
		cam->SetViewport(0, 0, w_SceneView->width(), w_SceneView->height());
	}
}

void DockArea::SaveState(std::string path)
{
	
	QSettings settings(
		QSettings::IniFormat,
		QSettings::SystemScope,
		"settings",
		"user");
	m_DockManager->addPerspective("custom");
	m_DockManager->savePerspectives(settings);




}

void DockArea::LoadState(std::string path) {


	QSettings settings(
		QSettings::IniFormat,
		QSettings::SystemScope,
		"settings",
		"user");
	m_DockManager->loadPerspectives(settings);
	m_DockManager->openPerspective("custom");
	

}