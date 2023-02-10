#include "SceneViewport.h"
#include "TrinityGlobal.h"
#include "SceneGraph.h"
#include "Node3D.h"
#include "Importer.h"

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
	//ViewportReady();
	TrinityGlobal::CurrentScene = new SceneGraph;
	auto g1 = TrinityGlobal::CurrentScene;

	auto imp = new Importer;

	auto root = imp->ImportEntity("test/test2.fbx");

	auto l1 = new NodeLight(true);

	l1->SetPosition(float3(0, 5, -20));
	l1->SetRange(250);


	g1->AddNode(root);
	g1->AddLight(l1);

	auto cam = g1->GetCamera();

	cam->SetPosition(float3(0, 5, -20));

	auto n1 = new Node3D;
	auto n2 = new Node3D;
	auto n3 = new Node3D;
	n1->SetName("Node 1");
	n2->SetName("Node 2");
	n3->SetName("Node 3");
//	g1->AddNode(n1);
//	g1->AddNode(n2);
	n1->AddNode(n3);

	for (int i = 0; i < 300;i++) {
		n3 = new Node3D;
		n3->SetName("NNNN");
		n1->AddNode(n3);
	}


}

void SceneViewport::RenderScene() {

	int a = 5;
	//mDraw->Begin();
	//mDraw->DrawTexture(20, 20, 256, 256, mTex1, 1, 1, 1, 1, false);
	//mDraw->End();
	auto g1 = TrinityGlobal::CurrentScene;
	g1->RenderShadowMaps();
	g1->Render();



}

