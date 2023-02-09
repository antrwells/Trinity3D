#include "QSceneGraph.h"

QSceneGraph::QSceneGraph(QWidget *parent)
	: CDockWidget("Scene Graph",parent)
{
	ui.setupUi(this);
}

QSceneGraph::~QSceneGraph()
{}
