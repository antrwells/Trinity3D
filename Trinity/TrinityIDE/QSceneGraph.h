#pragma once

#include <QWidget>
#include "ui_QSceneGraph.h"
#include "DockManager.h"
#include "SceneGraphWidget.h"

class QSceneGraph : public ads::CDockWidget
{
	Q_OBJECT

public:
	QSceneGraph(QWidget *parent = nullptr);
	~QSceneGraph();

protected:

	virtual void paintEvent(QPaintEvent* event);

private:

	SceneGraphWidget* w_SceneGraph;
	Ui::QSceneGraphClass ui;
};
