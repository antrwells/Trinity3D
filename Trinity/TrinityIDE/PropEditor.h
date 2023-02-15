#pragma once

#include <QWidget>
#include "ui_PropEditor.h"
#include "qscrollarea.h"
#include "PropEditorSurface.h"

class Node3D;

class PropEditor : public QScrollArea
{
	Q_OBJECT

public:
	PropEditor(QWidget *parent = nullptr);
	~PropEditor();
	void SetNode(Node3D* node);
	void ReSet();
protected:
	virtual void resizeEvent(QResizeEvent* event);

protected:
	void dragEnterEvent(QDragEnterEvent* event)
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
	Ui::PropEditorClass ui;
	//Node3D* mNode;
	PropEditorSurface* w_PropSurface;
};
