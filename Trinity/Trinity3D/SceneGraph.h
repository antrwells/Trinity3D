#pragma once
#include <vector>
#include "Node3D.h"
#include "CubeRenderer.h"
#include "MeshRenderer.h"

#include "VFile.h"





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

			void LoadGraph(std::string path);


			void ReadNode(VFile* file, Node3D* node);


			void WriteTransform(VFile* file, Node3D* node);

			void ReadTransform(VFile* file, Node3D* node);

			void SaveGraph(std::string path);
			
			Node3D* ReadNodeHeader(VFile* file);


			void SaveNodeHeader(VFile* file, Node3D* node);

			void SaveNode(VFile* file, Node3D* node);


			static SceneGraph* mThis;
			RayPicker* mRayPick = nullptr;
		
			

			std::vector<NodeCamera*> GetCams();

		//	MeshRenderer* GetRenderer();

			void SetCams(std::vector<NodeCamera*> cams);

			void SetMain();

			static SceneGraph* GetMainScene();

			void LoadCine(const char* path);

			MeshRenderer* GetRenderer() {
				return mRenderer;
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

