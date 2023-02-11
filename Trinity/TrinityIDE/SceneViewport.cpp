#include "SceneViewport.h"
#include "TrinityGlobal.h"
#include "SceneGraph.h"
#include "Node3D.h"
#include "NodeEntity.h"
#include "RayPicker.h"
#include "Importer.h"
#include "VString.h"
#include "MeshLines.h"

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
	mScaleGizmo = imp->ImportEntity("edit/gizmo/scale1.fbx");
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
	mTranslateGizmo->GetMesh(0)->SetName("Z");
	mTranslateGizmo->GetMesh(1)->SetName("X");
	mTranslateGizmo->GetMesh(2)->SetName("Y");
	mRotateGizmo->GetMesh(2)->SetName("X");
	mRotateGizmo->GetMesh(0)->SetName("Y");
	mRotateGizmo->GetMesh(1)->SetName("Z");
	mScaleGizmo->GetMesh(0)->SetName("X");
	mScaleGizmo->GetMesh(1)->SetName("Y");
	mScaleGizmo->GetMesh(2)->SetName("Z");

	mScaleGizmo->GetMesh(0)->GetMaterial()->SetColorMap(red_tex);
	mScaleGizmo->GetMesh(1)->GetMaterial()->SetColorMap(green_tex);
	mScaleGizmo->GetMesh(2)->GetMaterial()->SetColorMap(blue_tex);
	createGrid();
}

void SceneViewport::RenderScene() {

	int a = 5;
	//mDraw->Begin();
	//mDraw->DrawTexture(20, 20, 256, 256, mTex1, 1, 1, 1, 1, false);
	//mDraw->End();

	auto ren = TrinityGlobal::CurrentScene->GetRenderer();
	//if (mGridOn) {
		ren->RenderMeshLines(mEditGrid,mEditCam);
	//}

	auto g1 = TrinityGlobal::CurrentScene;
	g1->RenderShadowMaps();
	g1->Render();

	ClearDepth();

	auto mSelectedNode = TrinityGlobal::ActiveNode;

	if (mSelectedNode != nullptr) {



		//mCamGizmo->SetPosition(mSelectedNode->GetPosition());

		mCurrentGizmo->SetPosition(mSelectedNode->GetPositionWorld());


		//mCamGizmo->SetRotation4x4(mSelectedNode->GetRotation4x4().Inverse());
		if (mGizmoSpace == GizmoSpace::Local) {

			if (mSelectedNode->GetType() == NodeType::Camera) {
				mCurrentGizmo->SetRotation4x4(mSelectedNode->GetRotation4x4().Inverse());
			}
			else {
				mCurrentGizmo->SetRotation4x4(mSelectedNode->GetRotation4x4());
			}

		}
		else {
			mCurrentGizmo->SetRotation(0, 0, 0);
		}



	}

	if (TrinityGlobal::ActiveNode != nullptr) {
		//mCurrentGizmo->SetPosition(TrinityGlobal::ActiveNode->GetPosition());

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
	if (mLeftDown && gLock) {

		if (gLock) {

			if (TrinityGlobal::ActiveNode != nullptr) {

				float3 new_pos = TrinityGlobal::ActiveNode->GetPosition();
				float3 new_scale = TrinityGlobal::ActiveNode->GetScale();

				switch (mGizMode) {

				case GizmoMode::Translate:


					if (gLock_x)
					{

						if (mGizmoSpace == GizmoSpace::Global) {
							new_pos.x += (mMoveX) * mTranslateRatio;
							TrinityGlobal::ActiveNode->SetPosition(new_pos);
						}
						else {
							TrinityGlobal::ActiveNode->Move(float3(((float)mMoveX) * mTranslateRatio, 0, 0));

						}
					}
					if (gLock_y) {

						if (mGizmoSpace == GizmoSpace::Global) {
							new_pos.y += ((float)-mMoveY) * mTranslateRatio;
							TrinityGlobal::ActiveNode->SetPosition(new_pos);
						}
						else {
							TrinityGlobal::ActiveNode->Move(float3(0, ((float)mMoveY) * mTranslateRatio, 0));
						}

					}
					if (gLock_z) {

						if (mGizmoSpace == GizmoSpace::Global) {
							new_pos.z += ((float)-mMoveY) * mTranslateRatio;
							TrinityGlobal::ActiveNode->SetPosition(new_pos);
						}
						else {
							TrinityGlobal::ActiveNode->Move(float3(0, 0, ((float)mMoveY) * mTranslateRatio));
						}

					}
					break;
				case GizmoMode::Rotate:

					if (gLock_x) {

						if (mGizmoSpace == GizmoSpace::Local) {
							TrinityGlobal::ActiveNode->RotateLocal(((float)mMoveX * mRotateRatio), 0, 0);
						}
						else {
							TrinityGlobal::ActiveNode->RotateGlobal(((float)mMoveX * mRotateRatio), 0, 0);
						}
					}

					if (gLock_y) {

						if (mGizmoSpace == GizmoSpace::Local) {
							TrinityGlobal::ActiveNode->RotateLocal(0, ((float)mMoveX * mRotateRatio), 0);
						}
						else {
							TrinityGlobal::ActiveNode->RotateGlobal(0, ((float)mMoveX * mRotateRatio), 0);
						}
					}

					if (gLock_z) {

						if (mGizmoSpace == GizmoSpace::Local) {
							TrinityGlobal::ActiveNode->RotateLocal(0, 0, -((float)mMoveX * mRotateRatio));
						}
						else {
							TrinityGlobal::ActiveNode->RotateGlobal(0, 0, -((float)mMoveX * mRotateRatio));
						}

					}

					break;
				case GizmoMode::Scale:


					if (gLock_x)
					{


						new_scale.x += ((float)mMoveX) * mScaleRatio;
						TrinityGlobal::ActiveNode->SetScale(new_scale);

					}
					if (gLock_y) {


						new_scale.y += ((float)-mMoveY) * mScaleRatio;
						TrinityGlobal::ActiveNode->SetScale(new_scale);


					}
					if (gLock_z) {


						new_scale.z += ((float)-mMoveY) * mScaleRatio;
						TrinityGlobal::ActiveNode->SetScale(new_scale);

					}

					break;
				}


			}

		}

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
			mLeftDown = true;
			auto scene = TrinityGlobal::CurrentScene;
			auto res = scene->mRayPick->MousePick(mLastX, mLastY, width(), height(), scene->GetCamera());

			if (res.hit) {

				TrinityGlobal::ActiveNode = res.hit_node;
				std::string name = res.hit_node->GetName();

				std::string log = "Active Node:" + name;
				qDebug(log.c_str());


			}


			auto giz_result = scene->mRayPick->MousePickNode((int)mLastX, (int)mLastY, (int)width(), (int)height(), mCurrentGizmo, mEditCam);

			int bbb = 5;

			if (giz_result.hit) {
				VString giz_name = VString(giz_result.hit_mesh->GetName());

				if (giz_name.Contains(VString("X")))
				{
					gLock_x = true;
					gLock_y = false;
					gLock_z = false;
					gLock = true;
				}
				if (giz_name.Contains(VString("Y")))
				{
					gLock_x = false;
					gLock_y = true;
					gLock_z = false;
					gLock = true;
				}
				if (giz_name.Contains("Z")) {
					gLock_x = false;
					gLock_y = false;
					gLock_z = true;
					gLock = true;
				}
			}

			//}



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
		else if (mouseEvent->button() == Qt::LeftButton)
		{
			mLeftDown = false;
			gLock = false;
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

void SceneViewport::createGrid() {

	mEditGrid = new MeshLines;

	float x = -50;
	float z = -50;



	for (int i = 0; i < 100; i++) {

		float3 p1, p2;
		p1 = float3(x, 0, z);
		p2 = float3(x, 0, -z);

		mEditGrid->AddLine(p1, p2, float4(0.7, 0.7, 0.7, 1));

		x = x + 1.0f;

	}

	x = -50;

	for (int i = 0; i < 100; i++) {

		float3 p1, p2;
		p1 = float3(x, 0, z);
		p2 = float3(-x, 0, z);
		z = z + 1.0f;
		mEditGrid->AddLine(p1, p2, float4(0.5,0.5,0.5, 1));

	}
	mEditGrid->CreateBuffers();

}