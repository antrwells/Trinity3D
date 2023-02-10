#pragma once

#include <QWidget>
#include "ui_DockAreaWidget.h"
#include "QSceneGraph.h"
#include "SceneViewport.h"
class DockAreaWidget : public QWidget
{
	Q_OBJECT

public:
	DockAreaWidget(QWidget *parent = nullptr);
	~DockAreaWidget();
	void SetViewportMode(int mode)
	{
		w_SceneView->SetMode(mode);
	};

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	Ui::DockAreaWidgetClass ui;
	ads::CDockManager* m_DockManager;

	QSceneGraph* w_SceneGraph;
	SceneViewport* w_SceneView;
};
