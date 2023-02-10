#pragma once

#include <QMainWindow>
#include "ui_SceneGraphWidget.h"
#include "Node3D.h"
#include <QMouseEvent>
#include "qscrollbar.h"
class SceneGraphWidget : public QWidget
{
	Q_OBJECT

public:
	SceneGraphWidget(QWidget *parent = nullptr);
	~SceneGraphWidget();
	void SetScroller(QScrollBar* scroll) {
		mScrollLink = scroll;
		connect(scroll, &QScrollBar::valueChanged, this, &SceneGraphWidget::updateWidget);
	}

public slots:
	void updateWidget(int newValue)
	{
		update();
	}

protected:

	
	void CheckNode(Node3D* node, int& dx, int& dy,int mx,int my);
	void DrawNode(Node3D* node, int& dx, int& dy,QPainter& p);
	void GetMaxSize(Node3D* node, int& sy);

	virtual void paintEvent(QPaintEvent* event);
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

private:
	Ui::SceneGraphWidgetClass ui;
	Node3D* mCurrentNode = nullptr;
	Node3D* mActiveNode = nullptr;
	int max_y = 0;
	QScrollBar* mScrollLink;
};
