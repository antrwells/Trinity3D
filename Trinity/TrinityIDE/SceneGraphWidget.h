#pragma once

#include <QMainWindow>
#include "ui_SceneGraphWidget.h"
#include "Node3D.h"
#include <QMouseEvent>

class SceneGraphWidget : public QWidget
{
	Q_OBJECT

public:
	SceneGraphWidget(QWidget *parent = nullptr);
	~SceneGraphWidget();

protected:

	void CheckNode(Trinity::Scene::Node3D* node, int& dx, int& dy,int mx,int my);
	void DrawNode(Trinity::Scene::Node3D* node, int& dx, int& dy,QPainter& p);

	virtual void paintEvent(QPaintEvent* event);
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

private:
	Ui::SceneGraphWidgetClass ui;
	Trinity::Scene::Node3D* mCurrentNode = nullptr;
	Trinity::Scene::Node3D* mActiveNode = nullptr;

};
