#pragma once

#include <QWidget>
#include "ui_PropEditor.h"
#include "qscrollarea.h"

class Node3D;

class PropEditor : public QScrollArea
{
	Q_OBJECT

public:
	PropEditor(QWidget *parent = nullptr);
	~PropEditor();
	void SetNode(Node3D* node);

private:
	Ui::PropEditorClass ui;
	Node3D* mNode;
};
