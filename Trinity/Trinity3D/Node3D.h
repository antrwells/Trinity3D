 #pragma once
#include <vector>
//#include <glm/glm.hpp>
//#include <glm/common.hpp>
//#include "NodeComponent.h"

//#include "Effect.h"
#ifndef PLATFORM_WIN32
#    define PLATFORM_WIN32 1
#endif


//#include "NodeProperty.h"
#include "Common/interface/BasicMath.hpp"
#include "VFile.h"


class NodeEntity;
using namespace Diligent;



		enum NodeType {
			Entity, Node, Camera, Light, Other, Actor
		};

		/// <summary>
		/// Vivid::Graph::Nodes contains all the base-line graph nodes.
		/// </summary>

			/// Node3D is a empty 3D graph node. For rendering capabilities see NodeEntity.
			/// </summary>
		class Node3D
		{
		public:

			/// <summary>
			/// The base constructor, will place the node at 0,0,0 with no rotation and a scale of 1,1,1
			/// </summary>
			Node3D();

			NodeType GetType();

			virtual void UpdateActor() {};
			virtual void UpdateRotation() {};


			float3x3 GetRotation();

			void SetRotation3x3(float3x3 rot);

			Node3D* FindNode(std::string name);


			float4x4 GetRotation4x4();


			/// <summary>
			/// Updates a node and all it's children. Custom implentations of nodes may rely on this to function correctly.
			/// </summary>
			virtual void Update();


			/// <summary>
			/// All children will be updated.
			/// </summary>
			void UpdateChildren();


			/// <summary>
			/// returns the world matrix, which is the position, rotation and scale of a node, and is modulated by it's root nodes.
			/// </summary>
			/// <returns></returns>
			virtual float4x4 GetWorldMatrix();

			/// <summary>
			/// Adds a node component to the node, this is for extending functionality of nodes for games/apps.
			/// </summary>
			/// <param name="component"></param>



			/// <summary>
			/// Internal use.
			/// </summary>
			virtual void Render();
			/// <summary>
			/// Internal use.
			/// </summary>
			virtual void RenderDepth();
			/// <summary>
			/// Internal use.
			/// </summary>
			void RenderChildren();

			void RenderUI();

			/// <summary>
			/// Internal use.
			/// </summary>
			void RenderDepthChildren();

			/// <summary>
			/// Internal use.
			/// </summary>
			void SetRootNode(Node3D* node);

			/// <summary>
			/// Adds a node as a child of this node.
			/// </summary>
			/// <param name="node"></param>
			void AddNode(Node3D* node);

			/// <summary>
			/// Returns the 3D position of the node as a glm::vec3 
			/// </summary>
			/// <returns></returns>
			float3 GetPosition();

			float3 GetScale();

			/// <summary>
			/// Sets the 3D position of the node.
			/// </summary>
			/// <param name="position"></param>
			virtual void SetPosition(float3 position);

			/// <summary>
			/// Sets the euler rotation of the node.
			/// </summary>
			/// <param name="pitch"></param>
			/// <param name="yaw"></param>
			/// <param name="roll"></param>
			virtual void SetRotation(float pitch, float yaw, float roll);
			void SetRotation4x4(float4x4 rotation);
			void SetRotation(float4x4 mat);

			virtual void RotateLocal(float pitch, float yaw, float roll);
			virtual void RotateGlobal(float pitch, float yaw, float roll);

			/// <summary>
			/// Sets the scale of the node. Default is 1,1,1
			/// </summary>
			/// <param name="scale"></param>
			void SetScale(float3 scale);


			/// <summary>
			/// Moves the node with the given delta.
			/// </summary>
			/// <param name="move"></param>
			virtual void Move(float3 move);

			/// <summary>
			/// Points a node at the L vector.
			/// </summary>
			/// <param name="l"></param>
			/// <param name="up"></param>




			//	static Kinetic::FX::Effect* FXDepth;
			//	static Kinetic::FX::Effect* FXDepthAnim;

				/// <summary>
				/// Returnns how many children this node has.
				/// </summary>
				/// <returns></returns>
			size_t ChildrenCount();
			/// <summary>
			/// Internal use.
			/// </summary>
			virtual void UpdatePhysics() {};

			/// <summary>
			/// Returns the given child node. starts at 0.
			/// </summary>
			/// <param name="id"></param>
			/// <returns></returns>
			Node3D* GetChild(int id);

			/// <summary>
			/// Adds a custom property to the given node.
			/// </summary>
			/// <param name="property"></param>
			/// <returns></returns>
			//NodeProperty* AddProperty(NodeProperty* property);

			/// <summary>
			/// Returns the given property.
			/// </summary>
			/// <param name="name"></param>
			/// <returns></returns>
		//	NodeProperty* GetProperty(std::string name);

		//	std::vector<NodeProperty*> GetProperties();


			/// <summary>
			/// Clones a node, including any data asscoiated with it.
			/// </summary>
			/// <returns></returns>
			virtual Node3D* Clone() { return nullptr; };

			/// <summary>
			/// If called, the node will be removed from the current scene graph at the earliest possible moment.
			/// </summary>

			/// <summary>
			/// Returns true if the node is scheduled to be removed.
			/// </summary>

			/// <summary>
			/// Returns the root(parent) node of the node.
			/// </summary>
			/// <returns></returns>
			Node3D* GetRootNode();

			float3 GetPositionWorld();


			/// <summary>
			/// Removes a node from the children nodes.
			/// </summary>
			/// <param name="node"></param>
			void RemoveNode(Node3D* node);



			/// <summary>
			/// Sets the name of the node.
			/// </summary>
			/// <param name="name"></param>
			void SetName(const char* name);
			/// <summary>
			/// returns the name of the node.
			/// </summary>
			/// <returns></returns>
			const char* GetName();


			void SetHidden(bool hidden);

			bool IsHidden();

			void BeginNode();
			void EndNode();
			void AddSystemFunctions();

			virtual void ReadNode(VFile* file, bool read_type = true) {};

			void WriteScripts(VFile* file);
			void ReadScripts(VFile* file);

			/*
			virtual void WriteNode(VFile* file) {


				file->WriteInt((int)mType);
				file->WriteBool(mEnabled);
				file->WriteString(mName);
				//WriteTransform(file);

				file->WriteInt(0);

				WriteScripts(file);

				file->WriteInt((int)mChildren.size());
				for (int i = 0; i < mChildren.size(); i++) {

					mChildren[i]->WriteNode(file);

				}


			}
			*/


			void SetEnabled(bool enable);

			bool GetEnabled();

			void ClearNodes();


			bool IsPlaying();

			void SetPlaying(bool play);

		protected:

			static bool mSysInit;
			bool mTransformInvalidated = true;

			bool mQueueForRemove = false;

			Node3D* mRootNode = nullptr;
			std::string mPath = "None";

			/// <summary>
			/// Children of this node.
			/// </summary>
			std::vector<Node3D*> mChildren;

			//Placement
			float4x4 mRotation;
			float3 mPosition;
			float3 mScale;

			float4x4 mValidTransform;

			//name
			const char* mName;

			NodeType mType;

			bool mHidden = false;

			//Components
		//	std::vector<NodeComponent*> mComponents;

			//Properties
		//	std::vector<NodeProperty*> mProperties;



			float4x4 mPushRot;
			float3 mPushPos;
			float3 mPushScale;
			bool mChanged = false;
			bool mEnabled = true;
			bool mPlaying = false;
			
			//Editor specific
			public:
			bool mNodeOpen = true;


		}
		;

