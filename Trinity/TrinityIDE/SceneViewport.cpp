#include "SceneViewport.h"
#include "TrinityGlobal.h"
#include "SceneGraph.h"
#include "Node3D.h"

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
	mTex1 = new Trinity::Texture::Texture2D("test/img1.png");
	mDraw = new Trinity::Draw::SmartDraw(Trinity::App::TrinityApp::GetApp());
	//ViewportReady();
	TrinityGlobal::CurrentScene = new Trinity::Scene::SceneGraph;
	auto g1 = TrinityGlobal::CurrentScene;

	auto n1 = new Trinity::Scene::Node3D;
	auto n2 = new Trinity::Scene::Node3D;
	auto n3 = new Trinity::Scene::Node3D;
	n1->SetName("Node 1");
	n2->SetName("Node 2");
	n3->SetName("Node 3");
	g1->AddNode(n1);
	g1->AddNode(n2);
	n1->AddNode(n3);


}

void SceneViewport::RenderScene() {

	int a = 5;
	mDraw->Begin();
	mDraw->DrawTexture(20, 20, 256, 256, mTex1, 1, 1, 1, 1, false);
	mDraw->End();

}