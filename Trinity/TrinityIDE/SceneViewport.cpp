#include "SceneViewport.h"

SceneViewport::SceneViewport(QWidget *parent)
	: QDirect3D12Widget(parent)
{
	ui.setupUi(this);

	connect(this, &QDirect3D12Widget::LoadResources, this, &SceneViewport::LoadResources);
	connect(this, &QDirect3D12Widget::RenderScene, this, &SceneViewport::RenderScene);
}

SceneViewport::~SceneViewport()
{}

void SceneViewport::LoadResources() {

	int a = 5;
	mTex1 = new Texture2D("test/img1.png");
	mDraw = new SmartDraw(TrinityApp::GetApp());

}

void SceneViewport::RenderScene() {

	int a = 5;
	mDraw->Begin();
	mDraw->DrawTexture(20, 20, 256, 256, mTex1, 1, 1, 1, 1, false);
	mDraw->End();

}