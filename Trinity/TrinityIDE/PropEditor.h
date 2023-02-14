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

private:
	Ui::PropEditorClass ui;
	//Node3D* mNode;
	PropEditorSurface* w_PropSurface;
};
