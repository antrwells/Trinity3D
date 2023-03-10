#include "SceneViewport.h"
#include "TrinityGlobal.h"
#include "SceneGraph.h"
#include "Node3D.h"
#include "NodeEntity.h"
#include "RayPicker.h"
#include "Importer.h"
#include "VString.h"
#include "MeshLines.h"
#include "NodeEditorWidget.h"

SceneViewport::SceneViewport(QWidget *parent)
	: QDirect3D12Widget(parent)
{
	ui.setupUi(this);

	setMouseTracking(true);



	installEventFilter(this);

	//setAttribute(Qt::WA_PaintOnScreen, false);
	mThis = this;
	
	connect(this, &QDirect3D12Widget::LoadResources, this, &SceneViewport::LoadResources);
	connect(this, &QDirect3D12Widget::RenderScene, this, &SceneViewport::RenderScene);
	setAcceptDrops(true);
}

SceneViewport::~SceneViewport()
{}

SceneViewport* SceneViewport::mThis = nullptr;



void SceneViewport::LoadResources() {

	int a = 5;
	mTex1 = new Texture2D("test/img1.png");
	iconLight = new Texture2D("edit/sprites/light1.png");
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


//	g1->AddNode(root);
	g1->AddLight(l1);
//	g1->AddNode(r2);


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

	auto gg = TrinityGlobal::GameScene;

	if (gg == nullptr) {
		auto ren = TrinityGlobal::CurrentScene->GetRenderer();
		//if (mGridOn) {
		ren->RenderMeshLines(mEditGrid, mEditCam);
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
		auto mGraph = TrinityGlobal::CurrentScene;
		auto cam = mGraph->GetCamera();


		TrinityApp::GetApp()->ClearDepth();

		mDraw->Begin();

		for (int i = 0; i < mGraph->LightCount(); i++) {
			Node3D* entity = mGraph->GetLight(i);

			float lx, ly;

			lx = 20;
			ly = 20;
			float4x4 model = entity->GetWorldMatrix();
			//angX = angX + 0.1f;

			// Camera is at (0, 0, -5) looking along the Z axis
			float4x4 View = cam->GetWorldMatrix().Inverse();;// float4x4::Translation(0.f, 0.0f, 5.0f);

			// Get pretransform matrix that rotates the scene according the surface orientation
			//auto SrfPreTransform = GetSurfacePretransformMatrix(float3{ 0, 0, 1 });

			// Get projection matrix adjusted to the current screen orientation
			auto Proj = cam->GetProjectionMatrix();  //float4x4::Projection( Maths::Deg2Rad(70.0f), 1024.0f / 760.0f, 0.001f, 1000.0f, false);

			// Compute world-view-projection matrix
			float4x4 m_WorldViewProjMatrix = model * View * Proj;
			m_WorldViewProjMatrix = m_WorldViewProjMatrix.Transpose();


			float4 pos = m_WorldViewProjMatrix * float4(0, 0, 0, 1.0);

			pos.x /= pos.w;
			pos.y /= pos.w;

			pos.x = (0.5 + pos.x * 0.5) * width();//  mRenderTarget->GetWidth();
			pos.y = (0.5 - pos.y * 0.5) * height();// mRenderTarget->GetHeight();

			mDraw->DrawTexture(pos.x - 32, pos.y - 32, 64, 64, iconLight, 1, 1, 1, 1, false);
		//	if (real_pos.x > pos.x - 32 && real_pos.x<pos.x + 32 && real_pos.y>pos.y - 32 && real_pos.y < pos.y + 32)
		//	{
				//if (Application::GetApp()->GetInput()->IsMouseDown(0))
				//{
				//	mSelectedNode = entity;
				//	mEditNode = entity;
			//	}
			//}
		}

		mDraw->End();

	 TrinityApp::GetApp()->ClearDepth();


		if (TrinityGlobal::ActiveNode != nullptr) {
			//mCurrentGizmo->SetPosition(TrinityGlobal::ActiveNode->GetPosition());

			g1->RenderNodeBasic(mCurrentGizmo);
		}


		mEditCam->Move(float3(mCamMoveX * mSpeedMod, 0, mCamMoveY * mSpeedMod));

	}
	else {

		auto g1 = TrinityGlobal::GameScene;
		g1->Update();
		g1->RenderShadowMaps();
		g1->Render();

	}
	

}

void SceneViewport::mouseMoveEvent(QMouseEvent* event)
{
	if (TrinityGlobal::GameScene != nullptr) {

		return;

	}
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
							NodeEditorWidget::sThis->ReSet();
						}
						else {
							TrinityGlobal::ActiveNode->Move(float3(((float)mMoveX) * mTranslateRatio, 0, 0));
							NodeEditorWidget::sThis->ReSet();

						}
					}
					if (gLock_y) {

						if (mGizmoSpace == GizmoSpace::Global) {
							new_pos.y += ((float)-mMoveY) * mTranslateRatio;
							TrinityGlobal::ActiveNode->SetPosition(new_pos);
							NodeEditorWidget::sThis->ReSet();
						}
						else {
							TrinityGlobal::ActiveNode->Move(float3(0, ((float)mMoveY) * mTranslateRatio, 0));
							NodeEditorWidget::sThis->ReSet();
						}

					}
					if (gLock_z) {

						if (mGizmoSpace == GizmoSpace::Global) {
							new_pos.z += ((float)-mMoveY) * mTranslateRatio;
							TrinityGlobal::ActiveNode->SetPosition(new_pos);
							NodeEditorWidget::sThis->ReSet();
						}
						else {
							TrinityGlobal::ActiveNode->Move(float3(0, 0, ((float)mMoveY) * mTranslateRatio));
							NodeEditorWidget::sThis->ReSet();
						}

					}
					break;
				case GizmoMode::Rotate:

					if (gLock_x) {

						if (mGizmoSpace == GizmoSpace::Local) {
							TrinityGlobal::ActiveNode->RotateLocal(((float)mMoveX * mRotateRatio), 0, 0);
							NodeEditorWidget::sThis->ReSet();
						}
						else {
							TrinityGlobal::ActiveNode->RotateGlobal(((float)mMoveX * mRotateRatio), 0, 0);
							NodeEditorWidget::sThis->ReSet();
						}
					}

					if (gLock_y) {

						if (mGizmoSpace == GizmoSpace::Local) {
							TrinityGlobal::ActiveNode->RotateLocal(0, ((float)mMoveX * mRotateRatio), 0);
							NodeEditorWidget::sThis->ReSet();
						}
						else {
							TrinityGlobal::ActiveNode->RotateGlobal(0, ((float)mMoveX * mRotateRatio), 0);
							NodeEditorWidget::sThis->ReSet();
						}
					}

					if (gLock_z) {

						if (mGizmoSpace == GizmoSpace::Local) {
							TrinityGlobal::ActiveNode->RotateLocal(0, 0, -((float)mMoveX * mRotateRatio));
							NodeEditorWidget::sThis->ReSet();
						}
						else {
							TrinityGlobal::ActiveNode->RotateGlobal(0, 0, -((float)mMoveX * mRotateRatio));
							NodeEditorWidget::sThis->ReSet();
						}

					}

					break;
				case GizmoMode::Scale:


					if (gLock_x)
					{


						new_scale.x += ((float)mMoveX) * mScaleRatio;
						TrinityGlobal::ActiveNode->SetScale(new_scale);
						NodeEditorWidget::sThis->ReSet();

					}
					if (gLock_y) {


						new_scale.y += ((float)-mMoveY) * mScaleRatio;
						TrinityGlobal::ActiveNode->SetScale(new_scale);
						NodeEditorWidget::sThis->ReSet();


					}
					if (gLock_z) {


						new_scale.z += ((float)-mMoveY) * mScaleRatio;
						TrinityGlobal::ActiveNode->SetScale(new_scale);
						NodeEditorWidget::sThis->ReSet();

					}

					break;
				}


			}

		}

	}

}

void SceneViewport::mousePressEvent(QMouseEvent* event) {

	if (TrinityGlobal::GameScene!=nullptr) {

		return;

	}
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

			auto mGraph = TrinityGlobal::CurrentScene;
			auto cam = mGraph->GetCamera();

			mDraw->Begin();

			int realy = mLastY;

			for (int i = 0; i < mGraph->LightCount(); i++) {
				Node3D* entity = mGraph->GetLight(i);

				float lx, ly;

				lx = 20;
				ly = 20;
				float4x4 model = entity->GetWorldMatrix();
				//angX = angX + 0.1f;

				// Camera is at (0, 0, -5) looking along the Z axis
				float4x4 View = cam->GetWorldMatrix().Inverse();;// float4x4::Translation(0.f, 0.0f, 5.0f);

				// Get pretransform matrix that rotates the scene according the surface orientation
				//auto SrfPreTransform = GetSurfacePretransformMatrix(float3{ 0, 0, 1 });

				// Get projection matrix adjusted to the current screen orientation
				auto Proj = cam->GetProjectionMatrix();  //float4x4::Projection( Maths::Deg2Rad(70.0f), 1024.0f / 760.0f, 0.001f, 1000.0f, false);

				// Compute world-view-projection matrix
				float4x4 m_WorldViewProjMatrix = model * View * Proj;
				m_WorldViewProjMatrix = m_WorldViewProjMatrix.Transpose();


				float4 pos = m_WorldViewProjMatrix * float4(0, 0, 0, 1.0);

				pos.x /= pos.w;
				pos.y /= pos.w;

				pos.x = (0.5 + pos.x * 0.5) * width();//  mRenderTarget->GetWidth();
				pos.y = (0.5 - pos.y * 0.5) * height();// mRenderTarget->GetHeight();

				//mDraw->DrawTexture(pos.x - 32, pos.y - 32, 64, 64, iconLight, 1, 1, 1, 1, false);
					if (mLastX > pos.x - 32 && mLastX<pos.x + 32 && realy>pos.y - 32 && realy < pos.y + 32)
					{
						TrinityGlobal::ActiveNode = entity;
						NodeEditorWidget::sThis->SetNode(entity);

						//exit(1);
						//if (Application::GetApp()->GetInput()->IsMouseDown(0))
						// 
						//{
						//	mSelectedNode = entity;
						//	mEditNode = entity;
					//	}
					}
			}


			mLeftDown = true;
		
			auto scene = TrinityGlobal::CurrentScene;

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
					return;
				}
				if (giz_name.Contains(VString("Y")))
				{
					gLock_x = false;
					gLock_y = true;
					gLock_z = false;
					gLock = true;
					return;
				}
				if (giz_name.Contains("Z")) {
					gLock_x = false;
					gLock_y = false;
					gLock_z = true;
					gLock = true;
					return;
				}
			}

			//}


		
			auto res = scene->mRayPick->MousePick(mLastX, mLastY, width(), height(), scene->GetCamera());

			if (res.hit) {

				TrinityGlobal::ActiveNode = res.hit_node;
				NodeEditorWidget::sThis->SetNode(res.hit_node);
				std::string name = res.hit_node->GetName();
				

			}
		}

	}
}

bool SceneViewport::eventFilter(QObject* obj, QEvent* event)
{
	if (obj != this) {
		return QWidget::eventFilter(obj, event);
	}
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

void SceneViewport::Play() {

	if (mPlaying) return;
	auto mGameGraph = new SceneGraph;

	mGameGraph->SetRoot(TrinityGlobal::CurrentScene->GetRoot());
	mGameGraph->SetMain();
	mGameGraph->SetCamera(TrinityGlobal::CurrentScene->GetCamera());
	mGameGraph->SetCams(TrinityGlobal::CurrentScene->GetCams());
	mGameGraph->SetLights(TrinityGlobal::CurrentScene->GetLights());
	mGameGraph->BeginPlay();
	TrinityGlobal::GameScene = mGameGraph;

	//mGameGraph->SetRoot(new Node3D);

	//mGraph->BeginPlay();

	mPlaying = true;


}

void SceneViewport::StopPlay() {

	if (mPlaying == false) return;
	TrinityGlobal::GameScene = nullptr;
	TrinityGlobal::CurrentScene->EndPlay();
	mPlaying = false;
	NodeEditorWidget::sThis->SetNode(TrinityGlobal::ActiveNode);


}