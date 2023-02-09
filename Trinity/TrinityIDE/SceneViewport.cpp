#include "SceneViewport.h"

SceneViewport::SceneViewport(QWidget *parent)
	: QDirect3D12Widget(parent)
{
	ui.setupUi(this);

	connect(this, &QDirect3D12Widget::LoadResources, this, &SceneViewport::LoadResources);

}

SceneViewport::~SceneViewport()
{}

void SceneViewport::LoadResources() {

	int a = 5;
	mTex1 = new Texture2D("test/img1.png");

}