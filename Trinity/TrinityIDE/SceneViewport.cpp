#include "SceneViewport.h"
#include "TrinityGlobal.h"
#include "SceneGraph.h"
#include "Node3D.h"
#include "NodeEntity.h"
#include "RayPicker.h"
#include "Importer.h"

SceneViewport::SceneViewport(QWidget *parent)
	: QDirect3D12Widget(parent)
{
	ui.setupUi(this);

	setMouseTracking(true);

	installEventFilter(this);
	setAttribute(Qt::WA_PaintOnScreen, false);

	
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
	auto r2 = imp->ImportEntity("test/test2.fbx");
	auto l1 = new NodeLight(true);

	r2->SetPosition(float3(5, 0, 0));
	root->SetPosition(float3(-5, 0, 0));

	l1->SetPosition(float3(10, 5, -20));
	l1->SetRange(250);


	g1->AddNode(root);
	g1->AddLight(l1);
	g1->AddNode(r2);


	auto cam = g1->GetCamera();

	mEditCam = cam;

	mMoveX = mMoveY = mMoveZ = 0;

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

	mTranslateGizmo =imp->ImportEntity("edit/gizmo/translate1.fbx");
	mRotateGizmo = imp->ImportEntity("edit/gizmo/rotate1.fbx");
	mCurrentGizmo = mTranslateGizmo;
	auto red_tex = new Texture2D("edit/gizmo/red.png");
	auto blue_tex = new Texture2D("edit/gizmo/blue.png");
	auto green_tex = new Texture2D("edit/gizmo/green.png");
	mTranslateGizmo->GetMesh(0)->GetMaterial()->SetColorMap(blue_tex);
	mTranslateGizmo->GetMesh(1)->GetMaterial()->SetColorMap(red_tex);
	mTranslateGizmo->GetMesh(2)->GetMaterial()->SetColorMap(green_tex);
	mRotateGizmo->GetMesh(0)->GetMaterial()->SetColorMap(green_tex);
	mRotateGizmo->GetMesh(1)->GetMaterial()->SetColorMap(blue_tex);
	mRotateGizmo->GetMesh(2)->GetMaterial()->SetColorMap(red_tex);

}

void SceneViewport::RenderScene() {

	int a = 5;
	//mDraw->Begin();
	//mDraw->DrawTexture(20, 20, 256, 256, mTex1, 1, 1, 1, 1, false);
	//mDraw->End();
	auto g1 = TrinityGlobal::CurrentScene;
	g1->RenderShadowMaps();
	g1->Render();

	ClearDepth();

	if (TrinityGlobal::ActiveNode != nullptr) {
		mCurrentGizmo->SetPosition(TrinityGlobal::ActiveNode->GetPosition());

		g1->RenderNodeBasic(mCurrentGizmo);
	}


	mEditCam->Move(float3(mCamMoveX*mSpeedMod, 0, mCamMoveY*mSpeedMod));


}

void SceneViewport::mouseMoveEvent(QMouseEvent* event)
{
	
	int x, y;

	x = event->x();
	y = event->y();

	if (first_Move) {
		mLastX = x;
		mLastY = y;
		first_Move = false;
	}

	mMoveX = x - mLastX;
	mMoveY = y - mLastY;
	mLastX = x;
	mLastY = y;


	if (mRotateLock) {
		mCamPitch -= mMoveY;
		mCamYaw -= mMoveX;

		mEditCam->SetRotation(mCamPitch, mCamYaw, 0);

		update();
	}

}

void SceneViewport::mousePressEvent(QMouseEvent* event) {

	if (event->button() == Qt::RightButton)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			mRotateLock = true;
		}
		else {
			mRotateLock = false;
		}
	}
	if (event->button() == Qt::LeftButton) {

		if (event->type() == QEvent::MouseButtonPress)
		{

			auto scene = TrinityGlobal::CurrentScene;
			auto res = scene->mRayPick->MousePick(mLastX, mLastY, width(), height(),scene->GetCamera());

			if (res.hit) {

				TrinityGlobal::ActiveNode = res.hit_node;
				std::string name = res.hit_node->GetName();

				std::string log = "Active Node:" + name;
				qDebug(log.c_str());
				

			}



		}

	}
}

bool SceneViewport::eventFilter(QObject* obj, QEvent* event)
{
	if (event->type() == QEvent::MouseButtonRelease)
	{
		QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
		if (mouseEvent->button() == Qt::RightButton)
		{
			// left mouse button was released
			mRotateLock =false;
		}
		else if (mouseEvent->button() == Qt::RightButton)
		{

			//mRotateLock = fals
				//e;
			// right mouse button was released
		}
	}
	return QWidget::eventFilter(obj, event);
}

void SceneViewport::resizeEvent(QResizeEvent* event) {

	int aa = 5;
	if (TrinityGlobal::CurrentScene != nullptr) {
		auto cam = TrinityGlobal::CurrentScene->GetCamera();
		cam->SetViewport(0, 0, width(), height());
		TrinityApp::GetApp()->Resize(width(), height());
	}
}