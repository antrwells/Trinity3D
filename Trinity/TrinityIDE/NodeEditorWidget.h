#pragma once

#include <QWidget>
#include "ui_NodeEditorWidget.h"
#include "DockManager.h"
#include "PropEditor.h"
#include "qmimedata.h"
#include "qdrag.h"
#include <QDrag>


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

	void dragEnterEvent(QDragEnterEvent* event) override
	{
		if (event->mimeData()->hasText()) {
			if (event->mimeData()->property("type").toString() == QString("script"))
			{
				event->acceptProposedAction();
			}
		}
	}

	void dragMoveEvent(QDragMoveEvent* event)
	{
		if (event->mimeData()->hasText()) {
			if (event->mimeData()->property("type").toString() == QString("script"))
			{
				event->acceptProposedAction();
			}
		}
	}

	void dropEvent(QDropEvent* event)
	{
		if (event->mimeData()->hasText()) {

			if (event->mimeData()->property("type").toString() == QString("script"))
			{
				//	event->acceptProposedAction();

				//setText(event->mimeData()->text());
				event->acceptProposedAction();

				//	auto scene = TrinityGlobal::CurrentScene;

				//	auto node = scene->ReadNodeFromFile(std::string(event->mimeData()->text().toStdString()));

				//	scene->AddNode(node);

			}

		}
	}
private:
	Ui::NodeEditorWidgetClass ui;
	Node3D* mEditNode;
	PropEditor* w_Prop;
	
};
