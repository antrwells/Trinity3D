#pragma once

#include <QWidget>
#include "ui_NodeEditorWidget.h"
#include "DockManager.h"
#include "PropEditor.h"

class Node3D;
class NodeEntity;
class NodeLight;
class NodeCamera;

class NodeEditorWidget : public ads::CDockWidget
{
	Q_OBJECT

public:
	NodeEditorWidget(QWidget *parent = nullptr);
	~NodeEditorWidget();
	static NodeEditorWidget* sThis;
	void SetNode(Node3D* node);
	void ReSet();
protected:
	virtual void resizeEvent(QResizeEvent* event);

private:
	Ui::NodeEditorWidgetClass ui;
	Node3D* mEditNode;
	PropEditor* w_Prop;
	
};
