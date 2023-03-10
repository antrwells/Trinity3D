#include "pch.h"
#include "SceneGraph.h"

#include "VString.h"
#include "NodeCamera.h"
#include "NodeLight.h"
#include "NodeEntity.h"
#include "TrinityApp.h"
#include "RayPicker.h"

#define HIT_GROUP_STRIDE  2


void SceneGraph::RenderNodeBasic(NodeEntity* entity)
{

	if (entity->GetEnabled() == false) return;

	//int a = 5;
	//mRenderer->RenderSimple(entity, mCam);
	bool first = true;
	if (entity->GetMeshes().size() > 0) {


		mRenderer->RenderSimple(entity, mCam);
		first = false;

	}

	for (int i = 0; i < entity->ChildrenCount(); i++) {

		RenderNodeBasic((NodeEntity*)entity->GetChild(i));

	}

}


		void SceneGraph::ClearNodes() {

			mRootNode->ClearNodes();

		}

		void SceneGraph::AddCamera(NodeCamera* cam)
		{
			mCams.push_back(cam);
			AddNode(cam);
		}

		void SceneGraph::SetCamera(NodeCamera* cam) {
			mCam = cam;
		}

		//lights

		std::vector<NodeLight*> SceneGraph::GetLights() {

			return mLights;

		}

		void SceneGraph::SetLights(std::vector<NodeLight*> lights) {
			mLights = lights;
		}

	

		/// <summary>
		/// Clears all particles. Internal use.
		/// </summary>
		void SceneGraph::ClearParticles() {

			//mParticles.resize(0);

		}

		/// <summary>
		/// Internal use.
		/// </summary>
		/// <param name="nb"></param>
	

		

	
		Node3D* SceneGraph::GetRoot() {
			return mRootNode;
		}

		void SceneGraph::SetRoot(Node3D* node) {
			mRootNode = node;
		}
		void SceneGraph::Reset() {
			mLights.resize(0);

		}

		void SceneGraph::RemoveLight(Node3D* node)
		{
			std::vector<NodeLight*> new_list;
			for (int i = 0; i < mLights.size(); i++)
			{
				if (mLights[i] == node) {

				}
				else {
					new_list.push_back(mLights[i]);
				}
			}
			mLights = new_list;
		}

		SceneGraph::SceneGraph() {

			mRootNode = new Node3D();
			mCam = new NodeCamera;
			mRenderer = new MeshRenderer;
			mShadowRenderer = new CubeRenderer(this, nullptr);
			mRootNode->SetName("Scene Root");
			mThis = this;
			mRayPick = new RayPicker(this);
		//	mRayPick = new RayPicker(this);
		//	SceneGlobal::mCurrentScene = this;
			mCams.push_back(mCam);
		//	mGameUI = new GameUI;
			//	FXDepth = new Kinetic::FX::Effect("engine/shader/depthVS.glsl", "engine/shader/depthFS.glsl");
		//	mDraw = new SmartDraw(Application::GetApp());


		}

		Node3D* SceneGraph::FindNode(std::string name)
		{

			return mRootNode->FindNode(name);

		}
		void SceneGraph::PlayCine() {

			//mCurrentCine->Play();

		}
		void SceneGraph::Update() {

			if (mRootNode->GetEnabled() == true)
			{
				mRootNode->Update();
			}
			//if (mCurrentCine != nullptr) {

			//	mCurrentCine->Update();

	//		}

		//	for (int i = 0; i < mBillboards.size(); i++) {

		//		mBillboards[i]->Update();

	//		}

		//	std::vector<NodeBillboard*> new_list;

			//for (int i = 0; i < mBillboards.size(); i++) {

			//	if (mBillboards[i]->IsQueuedRemove()) {

			//	}
			//	else {
			//		new_list.push_back(mBillboards[i]);
			//	}

			//}

			//mBillboards = new_list;

			//***
			//Physics::Main->Simulate(0.45f);



			//UpdateNodePhysics(mRootNode);

			//CheckRemove(mRootNode);

		}

		void SceneGraph::CheckRemove(Node3D* node) {

			/*
			if (node->IsQueuedRemove()) {

				node->GetRootNode()->RemoveNode(node);

			}
			else {

				for (int i = 0; i < node->ChildrenCount(); i++) {
					CheckRemove(node->GetChild(i));

				}
			}
			*/

		}

		void SceneGraph::StartComponents() {

		//	mRootNode->StartComponents();

		}

		void SceneGraph::EndComponents() {

		//	mRootNode->EndComponents();

		}

		void SceneGraph::UpdateNodePhysics(Node3D* node) {

			node->UpdatePhysics();

			for (int i = 0; i < node->ChildrenCount(); i++) {

				auto child = node->GetChild(i);

				UpdateNodePhysics(child);

			}


		}

		void SetCam(int t, NodeCamera* cam) {
			//***
			/*
			switch (t) {
			case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
				cam->LookAtZero(glm::vec3(1, 0, 0), glm::vec3(0, -1, 0));
				break;
			case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
				cam->LookAtZero(glm::vec3(-1, 0, 0), glm::vec3(0, -1, 0));
				break;
			case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
				cam->LookAtZero(glm::vec3(0, -1, 0), glm::vec3(0, 0, -1));
				break;
			case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
				cam->LookAtZero(glm::vec3(0, 1, 0), glm::vec3(0, 0, 1));
				break;
			case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
				cam->LookAtZero(glm::vec3(0, 0, 1), glm::vec3(0, -1, 0));
				break;
			case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
				cam->LookAtZero(glm::vec3(0, 0, -1), glm::vec3(0, -1, 0));
				break;
			}
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			*/
		}
		//int NodeLight::ShadowMapRes = 1024;

		NodeCamera* scam = nullptr;


		void SceneGraph::DrawShadowMap(NodeLight* light) {

			return;
			/*
			
			if (!light->GetShadowMapping()) {
				return;
			}
			//Active = this;


			//	if (!Reshadow) return;
			//	Reshadow = false;
			NodeCamera* cam = GetCamera();



			if (scam == nullptr) {
				scam = new NodeCamera;

				scam->SetFOV(90);
				scam->SetMinZ(cam->GetMinZ());
				scam->SetMaxZ(cam->GetMaxZ());
				//***
				//scam->SetViewport(0, 0,ShadowMapRes, NodeLight::ShadowMapRes);
			}
			scam->SetPosition(light->GetPosition());


			//auto vp = scam->GetPosition();
			//vp.Z = -vp.Z;
			//scam->SetPosition(vp);

			/*
			glDisable(GL_BLEND);

			//glDisable(GL_SCISSOR_TEST);

			Kinetic::Graph::Nodes::NodeCamera* old = GetCamera();
			glClearColor((float)1, 1, 1, 1);

			int ShadowMapRes = Kinetic::Graph::Nodes::NodeLight::ShadowMapRes;

			SetCamera(scam);
			glViewport(0, 0, ShadowMapRes, ShadowMapRes);
			//scam->SetViewport(0, 0, ShadowMapRes, ShadowMapRes);

			Kinetic::Framebuffer::FramebufferCube* ShadowFB = light->GetShadowFB();
			Kinetic::FX::Global::EffectGlobal::CurrentCamera = mCam;
		//	FXDepth->bind();


			int tar = 0;//ShadowFB->SetFace(0);
			SetCam(tar, scam);

			RenderDepth();

			SetCam(ShadowFB->SetFace(1), scam);
			RenderDepth();

			SetCam(ShadowFB->SetFace(2), scam);
			RenderDepth();

			SetCam(ShadowFB->SetFace(3), scam);
			RenderDepth();

			SetCam(ShadowFB->SetFace(4), scam);
			RenderDepth();

			SetCam(ShadowFB->SetFace(5), scam);
			RenderDepth();

			SetCamera(old);

			ShadowFB->Release();
				//FXDepth->unbind();
			glViewport(0, 0, Kinetic::Info::AppInfo::aWidth, Kinetic::Info::AppInfo::aHeight);

			*/
		}


		/*
		void NodeLight::SetCam(int t, NodeCamera* cam) {

			switch (t) {
			case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
				cam->LookAtZero(glm::vec3(1, 0, 0), glm::vec3(0, -1, 0));
				break;
			case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
				cam->LookAtZero(glm::vec3(-1, 0, 0), glm::vec3(0, -1, 0));
				break;
			case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
				cam->LookAtZero(glm::vec3(0, -1, 0), glm::vec3(0, 0, -1));
				break;
			case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
				cam->LookAtZero(glm::vec3(0, 1, 0), glm::vec3(0, 0, 1));
				break;
			case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
				cam->LookAtZero(glm::vec3(0, 0, 1), glm::vec3(0, -1, 0));
				break;
			case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
				cam->LookAtZero(glm::vec3(0, 0, -1), glm::vec3(0, -1, 0));
				break;
			}
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		*/


		void SceneGraph::RenderShadowMaps() {

			for (int i = 0; i < mLights.size(); i++) {

				if (mLights[i]->GetEnabled() == false) continue;
				if (mLights[i]->GetCastShadows()) {

					mShadowRenderer->SetRenderTargetCube(mLights[i]->GetShadowCube());

					mShadowRenderer->RenderDepth(mLights[i]->GetPosition(), mLights[i]->GetRange());
				}
			}
			//	printf("DS:%d\n",(int)(et - bt));

		}


		void SceneGraph::RenderNodeDepth(NodeEntity* entity)
		{
			if (entity->GetEnabled() == false) return;
			bool first = true;
			if (entity->GetMeshes().size() > 0) {


				mRenderer->RenderDepth(entity, mCam);
				first = false;

			}

			for (int i = 0; i < entity->ChildrenCount(); i++) {
				if (entity->GetChild(i)->GetType() != NodeType::Light) {
					RenderNodeDepth((NodeEntity*)entity->GetChild(i));
				}

			}

		}


		void SceneGraph::RenderDepth() {
			const float ClearColor[] = { 1,1,1, 0.0f };


			if (RenderTargetCube::BoundTarget != nullptr)//|| RenderTarget2D::BoundTarget != nullptr)
			{

			}
			else {
				auto con = TrinityApp::GetApp()->GetContext();
				auto* pRTV = TrinityApp::GetApp()->GetSwap()->GetCurrentBackBufferRTV();
				// Let the engine perform required state transitions
				con->ClearRenderTarget(pRTV, ClearColor, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
				//con->ClearDepthStencil(pDSV, CLEAR_DEPTH_FLAG, 1.f, 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
			}

			for (int i = 0; i < mRootNode->ChildrenCount(); i++)
			{
				auto node = mRootNode->GetChild(i);

				if (node->GetType() == NodeType::Entity)
				{

					auto entity = (NodeEntity*)mRootNode->GetChild(i);

					if (entity->IsHidden()) continue;
					if (entity->GetEnabled() == false) continue;

					RenderNodeDepth((NodeEntity*)entity);
				}
				if (node->GetType() == NodeType::Actor)
				{
					///TOFIX
					/*
					auto actor = (NodeActor*)mRootNode->GetChild(i);
					if (actor->IsHidden()) continue;
					if (actor->GetEnabled() == false) continue;
					RenderNodeActorDepth(actor);
					*/

				}
			}

			/*
			const float ClearColor[] = { 1,1,1, 0.0f };


			if (RenderTargetCube::BoundTarget != nullptr || RenderTarget2D::BoundTarget != nullptr)
			{

			}
			else {
				auto con = Application::GetApp()->GetContext();
				auto* pRTV = Application::GetApp()->GetSwap()->GetCurrentBackBufferRTV();
				// Let the engine perform required state transitions
				con->ClearRenderTarget(pRTV, ClearColor, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
				//con->ClearDepthStencil(pDSV, CLEAR_DEPTH_FLAG, 1.f, 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
			}

			for (int i = 0; i < mRootNode->ChildrenCount(); i++)
			{
				auto node = mRootNode->GetChild(i);

				if (node->GetType() == NodeType::Entity)
				{

					auto entity = (NodeEntity*)mRootNode->GetChild(i);

					if (entity->IsHidden()) continue;
					if (entity->GetEnabled() == false) continue;

					RenderNodeDepth((NodeEntity*)entity);
				}
				if (node->GetType() == NodeType::Actor)
				{

					auto actor = (NodeActor*)mRootNode->GetChild(i);
					if (actor->IsHidden()) continue;
					if (actor->GetEnabled() == false) continue;
					RenderNodeActorDepth(actor);


				}
			}

			//printf("RDTime:%d\n", (int)(et - bt));
			*/

		}

		void SceneGraph::PreRender() {

		}

	

		void SceneGraph::AddNode(Node3D* node)
		{

			mRootNode->AddNode(node);

		}


		void SceneGraph::AddNodeTemp(Node3D* node)
		{

	//		mRootNode->AddNodeTemp(node);

		}

		NodeCamera* SceneGraph::GetCamera() {

			return mCam;

		}

		void SceneGraph::AddLight(NodeLight* light, bool addtoscene) {

			mLights.push_back(light);
			//if (addtoscene) {
			mRootNode->AddNode(light);
			//}
		}

		int SceneGraph::LightCount() {

			return mLights.size();

		}

		NodeLight* SceneGraph::GetLight(int i) {

			return mLights[i];

		}

		void SceneGraph::CheckRT(Node3D* node) {

			if (node->GetType() == NodeType::Entity)
			{
				//printf("Found Entity Node.\n");
				NodeEntity* entity = (NodeEntity*)node;

				//			for (int i = 0;i < entity->GetMeshes().size();i++) {

				//mRTNodes.push_back(entity);

			



			}

			if (node->GetType() == NodeType::Actor) {

				


//				auto mesh_actor = actor->GetMesh(0);

				//mRTMeshes.push_back(mesh_actor);
				//for (int i = 0;i < entity->GetMeshes().size();i++) {

					//mRTMeshes.push_back(mesh_actor);

				//}

			}

			for (int i = 0; i < node->ChildrenCount(); i++) {

				CheckRT(node->GetChild(i));

			}

		}

		void SceneGraph::UpdateRT() {

			
		}

		void SceneGraph::BeginNode(Node3D* node) {
			if (node->GetEnabled() == false) return;
			node->SetPlaying(true);
			node->BeginNode();

			for (int i = 0; i < node->ChildrenCount(); i++)
			{
				BeginNode(node->GetChild(i));
			}

		}

		void SceneGraph::EndNode(Node3D* node)
		{
			if (node->GetEnabled() == false) return;
			node->EndNode();
			node->SetPlaying(false);
			if (node->GetType() == NodeType::Actor)
			{
				auto act = (NodeActor*)node;
				//act->StopAnim();
			}
			for (int i = 0; i < node->ChildrenCount(); i++) {
				EndNode(node->GetChild(i));
			}
		}

	

		

		void SceneGraph::BeginPlay() {

		//	ClearPhysics(mRootNode);
		//	BeginPhysics(mRootNode);
		//	BeginNode(mRootNode);
			//ClearPhysics(mRootNode);
			//BeginPhysics(mRootNode);
			BeginNode(mRootNode);
		}

		void SceneGraph::EndPlay() {

			EndNode(mRootNode);
		//	Audio::EndSong();

		}

		void SceneGraph::RenderNodeUI(Node3D* node) {

		
		}

		void SceneGraph::RenderUI(float4x4 proj) {

			//GameUI::UI->Begin();
			//RenderNodeUI(mRootNode);
			//GameUI::UI->End(proj);
		}


		SceneGraph* SceneGraph::mThis = nullptr;
		SceneGraph* SceneGraph::mMainScene = nullptr;


		void SceneGraph::Render() {

			for (int i = 0; i < mRootNode->ChildrenCount(); i++)
			{
				auto node = mRootNode->GetChild(i);

				if (node->GetType() == NodeType::Entity) {

					auto entity = (NodeEntity*)mRootNode->GetChild(i);

					if (entity->IsHidden()) continue;
					if (entity->GetEnabled() == false) continue;

					RenderNodeLit((NodeEntity*)entity);
				}
				if (node->GetType() == NodeType::Actor) {

					if (node->GetEnabled() == false) continue;
					//RenderNodeActorLit((NodeActor*)node);

				}
			}



		}

		void SceneGraph::RenderNodeLit(NodeEntity* entity) {

			bool first = true;
			if (entity->GetType() == NodeType::Entity) {
				if (entity->GetEnabled() == false) return;
				if (entity->GetMeshes().size() > 0) {
					for (int i = 0; i < mLights.size(); i++)
					{
						if (mLights[i]->GetEnabled() == false) continue;
						mRenderer->RenderLit(entity, mCam, mLights[i], first);
						first = false;
					}
				}
			}

			for (int i = 0; i < entity->ChildrenCount(); i++) {

				RenderNodeLit((NodeEntity*)entity->GetChild(i));

			}

		}
