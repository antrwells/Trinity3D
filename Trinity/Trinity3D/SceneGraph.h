#pragma once
#include <vector>
#include "Node3D.h"
#include "CubeRenderer.h"
#include "MeshRenderer.h"

#include "VFile.h"
#include "NodeProperty.h"




		/*
		struct TexItem {

			Texture2D* color;
			Texture2D* normal;
			Texture2D* specular;

		};
		*/

		class CubeRenderer;
		class GameUI;
		class RayPicker;
		class Cinematic;
		class NodeLight;
		class NodeCamera;
		/// <summary>
		/// Vivid::Graph is the namespace for the Vivid3D scene graph, this is what allows you to construct/render and update game scenes.
		/// </summary>

			/// <summary>
			/// SceneGraph is the base class for any type of scene graph.
			/// </summary>
		class SceneGraph
		{
		public:

			/// <summary>
			/// Initializes an empty scene Graph.
			/// </summary>
			SceneGraph();

			void ClearNodes();

			void AddCamera(NodeCamera* cam);

			void AddNodeTemp(Node3D* node);

			/// <summary>
			/// Will update the scene graph by calling each node's update method.
			/// </summary>
			void Update();
			void PlayCine();

			Node3D* FindNode(std::string name);

			/// <summary>
			/// Internal use.
			/// </summary>
			void StartComponents();
			/// <summary>
			/// internal use.
			/// </summary>
			void EndComponents();
			/// <summary>
			/// Internal use.
			/// </summary>
			void PauseComponents();
			/// <summary>
			/// Internal use.
			/// </summary>
			void ResumeComponents();
			/// <summary>
			/// Internal use.
			/// </summary>
			void SaveState();
			/// <summary>
			/// Internal use.
			/// </summary>
			void RestoreState();

			/// <summary>
			/// Internal use.
			/// </summary>
			/// <param name="node"></param>
			void UpdateNodePhysics(Node3D* node);
			void UpdatePhyscs()
			{
				UpdateNodePhysics(mRootNode);
			}
			/// <summary>
			/// Internal use.
			/// </summary>
			/// <param name="light"></param>
			void DrawShadowMap(NodeLight* light);
			/// <summary>
			/// Internal use.
			/// </summary>
			void RenderShadowMaps();

			/// <summary>
			/// Internal use.
			/// </summary>
			void RenderDepth();

			/// <summary>
			/// Internal use.
			/// </summary>
			/// <param name="node"></param>
			void CheckRemove(Node3D* node);

			/// <summary>
			/// Pre-Render is to generate/render any framebuffers needed for the final render, such as CubeMaps and ShadowMaps
			/// </summary>
			void PreRender();

			/// <summary>
			/// Will render the final scene.
			/// </summary>
			void Render();

			void RenderTextures();

			void RenderNormals();

			void RenderPositions();

			/// <summary>
			/// Will render anything needed post-render.
			/// </summary>
			void PostRender();


			/// <summary>
			/// Adds a node to the root node.
			/// </summary>
			/// <param name="node"></param>
			void AddNode(Node3D* node);

			/// <summary>
			/// Returns the active camera being used by the SceneGraph
			/// </summary>
			/// <returns></returns>
			NodeCamera* GetCamera();

			/// <summary>
			/// Sets the active camera.
			/// </summary>
			/// <param name="cam"></param>
			void SetCamera(NodeCamera* cam);

			//lights

			std::vector<NodeLight*> GetLights();


			void SetLights(std::vector<NodeLight*> lights);
			/// <summary>
			/// Adds a light to the scene. You can use as many as you'd like.
			/// </summary>
			/// <param name="light"></param>
			void AddLight(NodeLight* light, bool addtoscene = true);

			/// <summary>
			/// Adds a billboard to the scene.
			/// </summary>
			/// <param name="billboard"></param>
		//	void AddBillboard(NodeBillboard* billboard);

			/// <summary>
			/// Clears all particles. Internal use.
			/// </summary>
			void ClearParticles();

			/// <summary>
			/// Internal use.
			/// </summary>
			/// <param name="nb"></param>
		//	void AddParticle(NodeBillboard* nb);
			void RenderNodeNormals(NodeEntity* entity);
			void RenderNodeLit(NodeEntity* node);
			void RenderNodeBasic(NodeEntity* entity);
		
		//	void RenderNodeActorLit(NodeActor* actor);
		//	void RenderNodeActorDepth(NodeActor* actor);
			void RenderNodeDepth(NodeEntity* entity);
			void RenderNodePositions(NodeEntity* entity);

			int LightCount();
			NodeLight* GetLight(int i);

			void CheckRT(Node3D* node);
			void UpdateRT();
		//	RefCntAutoPtr<ITopLevelAS> GetTLAS();

			size_t RTInstanceCount();
	//		std::vector<TexItem> GetRTTextureList();

	//		Mesh3D* GetRTInstance(int id);

		//	BigBuffer* GetRTBigBuffer();


			Node3D* GetRoot();

			void RenderNodeUI(Node3D* node);
			void RenderUI(float4x4 proj);

			void EndNode(Node3D* node);
			void BeginNode(Node3D* node);
			void BeginPlay();
			void EndPlay();

			void SetRoot(Node3D* node);

			void Reset();

			void RemoveLight(Node3D* node);

			void LoadGraph(std::string path)
			{
				VFile* file = new VFile(path.c_str(), FileMode::Read);

				//Node3D* root = new Node3D;
				mLights.resize(0);
			

				mRootNode = ReadNodeHeader(file);
				ReadNode(file, mRootNode);
				mProperties.resize(0);

				int pc = file->ReadInt();
				for (int i = 0; i < pc; i++) {


					PropertyType type = (PropertyType)file->ReadInt();
					std::string name(file->ReadString());

					NodeProperty* prop = new NodeProperty(name);
					prop->SetType(type);
					switch (type) {
					case PropertyType::Int:
						prop->SetInt(file->ReadInt());
						break;
					case PropertyType::Float:
						prop->SetFloat(file->ReadFloat());
						break;
					case PropertyType::Float2:

					{float x, y;
					x = file->ReadFloat();
					y = file->ReadFloat();
					prop->SetFloat2(float2(x, y));
					}
					break;
					case PropertyType::Float3:
						prop->SetFloat3(file->ReadVec3());
						break;
					case PropertyType::Bool:
						prop->SetBool(file->ReadBool());
						break;
					case PropertyType::String:
						prop->SetString(file->ReadString());
						break;
					}
					mProperties.push_back(prop);
				}

				file->Close();
			}





			void WriteTransform(VFile* file, Node3D* node) {

				file->WriteVec3(node->GetPosition());
				file->WriteVec3(node->GetScale());
				file->WriteMatrix(node->GetRotation4x4());

			}
			void ReadTransform(VFile* file, Node3D* node) {

				node->SetPosition(file->ReadVec3());
				node->SetScale(file->ReadVec3());
				node->SetRotation(file->ReadMatrix());


			}

			void SaveGraph(std::string path)
			{

				VFile* file = new VFile(path.c_str(), FileMode::Write);
				SaveNodeHeader(file, mRootNode);
				SaveNode(file, mRootNode);

				file->WriteInt((int)mProperties.size());
				for (int i = 0; i < mProperties.size(); i++) {

					auto prop = mProperties[i];
					file->WriteInt((int)prop->GetType());
					file->WriteString(prop->GetName().c_str());
					switch (prop->GetType()) {
					case PropertyType::Int:
						file->WriteInt(prop->GetInt());
						break;
					case PropertyType::Float:
						file->WriteFloat(prop->GetFloat());
						break;
					case PropertyType::Float2:
						file->WriteFloat(prop->GetFloat2().x);
						file->WriteFloat(prop->GetFloat2().y);
						break;
					case PropertyType::Float3:
						file->WriteVec3(prop->GetFloat3());
						break;
					case PropertyType::Bool:
						file->WriteBool(prop->GetBool());
						break;
					case PropertyType::String:
						file->WriteString(prop->GetString().c_str());
						break;
					}
				}
				//SaveProperties - > Global 
				file->Close();

			}
	


		


			static SceneGraph* mThis;
			RayPicker* mRayPick = nullptr;
		
			

			std::vector<NodeCamera*> GetCams()
			{
				return mCams;
			}

		//	MeshRenderer* GetRenderer();

			void SetCams(std::vector<NodeCamera*> cams)
			{
				mCams = cams;
			}

			void SetMain()
			{
				mMainScene = this;
			}
			static SceneGraph* GetMainScene() {
				return mMainScene;
			}

			void LoadCine(const char* path);

			MeshRenderer* GetRenderer() {
				return mRenderer;
			}

			//load/save
			void SaveNodeHeader(VFile* file, Node3D* node) {

				file->WriteInt((int)node->GetType());
				file->WriteString(node->GetName().c_str());
				file->WriteBool(node->GetEnabled());
				WriteTransform(file, node);

			}

			void SaveNodeToFile(std::string path, Node3D* node) {

				VFile* file = new VFile(path.c_str(), FileMode::Write);
				SaveNodeHeader(file,node);
				SaveNode(file, node);

				file->Close();

			}

			void SaveNode(VFile* file, Node3D* node)
			{
				switch (node->GetType())
				{
				case NodeType::Actor:
				{
					/*

					auto ent = (NodeActor*)node;

					file->WriteInt((int)ent->GetMeshes().size());
					for (int i = 0; i < ent->GetMeshes().size(); i++) {

						ent->GetMesh(i)->WriteMesh(file);


					}

					ent->WriteScripts(file);
					file->WriteInt((int)ent->GetPhysicsType());

					//write anims
					ent->WriteAnimations(file);

					file->WriteInt((int)node->ChildrenCount());
					for (int i = 0; i < node->ChildrenCount(); i++) {

						auto sub = node->GetChild(i);
						SaveNodeHeader(file, sub);
						SaveNode(file, sub);
						//mChildren[i]->WriteNode(file);

					}
					*/
				}
				

				break;
				case NodeType::Node:
				{
					node->WriteScripts(file);

					file->WriteInt((int)node->ChildrenCount());
					for (int i = 0; i < node->ChildrenCount(); i++) {

						auto sub = node->GetChild(i);
						SaveNodeHeader(file, sub);
						SaveNode(file, sub);
						//mChildren[i]->WriteNode(file);

					}

				}
				break;
				case NodeType::Entity:
				{
					auto ent = (NodeEntity*)node;

					file->WriteInt((int)ent->GetMeshes().size());
					for (int i = 0; i < ent->GetMeshes().size(); i++) {

						ent->GetMesh(i)->WriteMesh(file);


					}

					ent->WriteScripts(file);
					file->WriteInt((int)ent->GetPhysicsType());

					file->WriteInt((int)node->ChildrenCount());
					for (int i = 0; i < node->ChildrenCount(); i++) {

						auto sub = node->GetChild(i);
						SaveNodeHeader(file, sub);
						SaveNode(file, sub);
						//mChildren[i]->WriteNode(file);

					}
				}
				break;
				case NodeType::Light:
				{
					auto l = (NodeLight*)node;

					file->WriteVec3(l->GetDiffuse());
					file->WriteVec3(l->GetSpecular());
					file->WriteFloat(l->GetRange());
					file->WriteBool(l->GetCastShadows());

					node->WriteScripts(file);

					file->WriteInt((int)node->ChildrenCount());
					for (int i = 0; i < node->ChildrenCount(); i++) {

						auto sub = node->GetChild(i);
						SaveNodeHeader(file, sub);
						SaveNode(file, sub);
						//mChildren[i]->WriteNode(file);

					}
				}
				break;
				}



			}
			Node3D* ReadNodeHeader(VFile* file) {

				Node3D* res = nullptr;
				NodeType type = (NodeType)file->ReadInt();
				switch (type) {
				case NodeType::Actor:
				//	res = new NodeActor;
					break;
				case NodeType::Node:
					res = new Node3D;
					break;
				case NodeType::Entity:
					res = new NodeEntity;
					break;
				case NodeType::Light:
					res = new NodeLight;
					mLights.push_back((NodeLight*)res);
					break;
				case NodeType::Camera:
					res = new NodeCamera;
					mCams.push_back((NodeCamera*)res);
					if (mCam == nullptr) {
						mCam = (NodeCamera*)res;
					}
					//mCams.push_back((NodeCamera*)res);

					break;
				}

				res->SetName(file->ReadString());
				res->SetEnabled(file->ReadBool());
				ReadTransform(file, res);
				return res;
			}


			Node3D* ReadNodeFromFile(std::string path) {

				VFile* file = new VFile(path.c_str(), FileMode::Read);


				auto res = ReadNodeHeader(file);
				ReadNode(file,res);

				file->Close();

				return res;

			}
			

			void ReadNode(VFile* file, Node3D* node)
			{
				switch (node->GetType()) {
				case NodeType::Node:
				{
					node->ReadScripts(file);

					int cc = file->ReadInt();
					for (int i = 0; i < cc; i++) {

						auto sub = ReadNodeHeader(file);
						ReadNode(file, sub);
						node->AddNode(sub);

					}
				}
				break;
				case NodeType::Actor:
				{
					/*
					auto ent = (NodeActor*)node;

					int mc = file->ReadInt();
					for (int i = 0; i < mc; i++) {

						Mesh3D* mesh = new Mesh3D();
						mesh->ReadMesh(file, true);
						ent->AddMesh(mesh);
						mesh->SetOwner(node);


					}

					node->ReadScripts(file);
					ent->SetPhysicsType((PhysicsType)file->ReadInt());

					ent->ReadAnimations(file);
					ent->GetAnimator()->ResetBones();

					int cc = file->ReadInt();
					for (int i = 0; i < cc; i++) {

						auto sub = ReadNodeHeader(file);
						ReadNode(file, sub);
						node->AddNode(sub);

					}
					*/
				}
				break;
				case NodeType::Entity:
				{
					auto ent = (NodeEntity*)node;

					int mc = file->ReadInt();
					for (int i = 0; i < mc; i++) {

						Mesh3D* mesh = new Mesh3D();
						mesh->ReadMesh(file);
						ent->AddMesh(mesh);
						mesh->SetOwner(node);


					}

					node->ReadScripts(file);
					ent->SetPhysicsType((PhysicsType)file->ReadInt());



					int cc = file->ReadInt();
					for (int i = 0; i < cc; i++) {

						auto sub = ReadNodeHeader(file);
						ReadNode(file, sub);
						node->AddNode(sub);

					}

				}
				break;
				case NodeType::Light:
				{
					auto l = (NodeLight*)node;
					l->SetDiffuse(file->ReadVec3());
					l->SetSpecular(file->ReadVec3());
					l->SetRange(file->ReadFloat());
					l->SetCastShadows(file->ReadBool());

					l->ReadScripts(file);


					int cc = file->ReadInt();
					for (int i = 0; i < cc; i++) {

						auto sub = ReadNodeHeader(file);
						ReadNode(file, sub);
						node->AddNode(sub);


					}
				}
				break;
				case NodeType::Camera:
					break;
				}
			}

			void ReloadMaterials() {
				mRootNode->ReloadMaterials();
			}

		private:
			static SceneGraph* mMainScene;

			std::vector<NodeCamera*> mCams;
			//std::vector<Node3D*> mRTNodes;
			//std::vector<Mesh3D*> mRTMeshes;
			//Kinetic::FX::Effect* FXDepth;

			std::vector<NodeLight*> mLights;

	//		std::vector<Node3D*> mNoRender;
		//	std::vector<TexItem> mRTTextureList;


			/// <summary>
			/// The root node of the graph, a root node can contain child nodes, creating the graph structurally.
			/// </summary>
			Node3D* mRootNode;
			//std::vector<NodeBillboard*> mBillboards;

			//std::vector<NodeBillboard*> mParticles;
			std::vector<NodeProperty*> mProperties;
			NodeCamera* mCam;
			//RayPicker* mRayPick = nullptr;
			MeshRenderer* mRenderer;
			CubeRenderer* mShadowRenderer;
		//	RefCntAutoPtr<ITopLevelAS> mTLAS;
		//	RefCntAutoPtr<IBuffer>             m_ScratchBuffer;
		//	RefCntAutoPtr<IBuffer>             m_InstanceBuffer;
	
			//GameUI* mGameUI;
			//SmartDraw* mDraw;
			//Cinematic* mCurrentCine = nullptr;
		};

