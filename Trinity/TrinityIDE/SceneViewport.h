#pragma once

#include <QWidget>
#include "ui_SceneViewport.h"
#include "QDirect3D12Widget.h"

class SceneViewport : public QDirect3D12Widget
{
	Q_OBJECT

public:
	SceneViewport(QWidget *parent = nullptr);
	~SceneViewport();

private:
	Ui::SceneViewportClass ui;
};
