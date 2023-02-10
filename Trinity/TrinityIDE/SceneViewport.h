#pragma once

#include <QWidget>
#include "ui_SceneViewport.h"
#include "QDirect3D12Widget.h"
#include "Texture2D.h"
#include "SmartDraw.h"

class SceneViewport : public QDirect3D12Widget
{
	Q_OBJECT

signals:

	void ViewportReady();

public:
	SceneViewport(QWidget *parent = nullptr);
	~SceneViewport();


private slots:
	void LoadResources();
	void RenderScene();

private:
	Ui::SceneViewportClass ui;
	Trinity::Texture::Texture2D* mTex1;
	Trinity::Draw::SmartDraw* mDraw;

	
};

