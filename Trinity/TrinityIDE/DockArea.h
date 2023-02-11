#pragma once

#include <QWidget>
#include "ui_DockAreaWidget.h"
#include "QSceneGraph.h"
#include "SceneViewport.h"
#include "ContentBrowserWidget.h"
#include <string>
#include "qsettings.h"
class DockArea : public QWidget
{
	Q_OBJECT

public:
	DockArea(QWidget *parent = nullptr);
	~DockArea();
	void SetViewportMode(int mode)
	{
		w_SceneView->SetMode(mode);
	};
	void SetViewportLocalMode(int mode) {
		w_SceneView->SetSpace(mode);
	}

	void SaveState(std::string path);
	void LoadState(std::string path);

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	Ui::DockAreaWidgetClass ui;
	ads::CDockManager* m_DockManager;

	QSceneGraph* w_SceneGraph;
	SceneViewport* w_SceneView;
	ContentBrowserWidget* w_ContentBrowser;
	QSettings settings;
};
