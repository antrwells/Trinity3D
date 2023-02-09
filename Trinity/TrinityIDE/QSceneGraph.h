#pragma once

#include <QWidget>
#include "ui_QSceneGraph.h"
#include "DockManager.h"

class QSceneGraph : public ads::CDockWidget
{
	Q_OBJECT

public:
	QSceneGraph(QWidget *parent = nullptr);
	~QSceneGraph();

private:
	Ui::QSceneGraphClass ui;
};
