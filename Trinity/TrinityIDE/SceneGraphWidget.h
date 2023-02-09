#pragma once

#include <QMainWindow>
#include "ui_SceneGraphWidget.h"

class SceneGraphWidget : public QMainWindow
{
	Q_OBJECT

public:
	SceneGraphWidget(QWidget *parent = nullptr);
	~SceneGraphWidget();

private:
	Ui::SceneGraphWidgetClass ui;
};
