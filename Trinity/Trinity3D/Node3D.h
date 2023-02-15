 #pragma once
#include <vector>
//#include <glm/glm.hpp>
//#include <glm/common.hpp>
//#include "NodeComponent.h"

//#include "Effect.h"
#ifndef PLATFORM_WIN32
#    define PLATFORM_WIN32 1
#endif
#include <cmath>

//#include "NodeProperty.h"
#include "Common/interface/BasicMath.hpp"
#include "VFile.h"

class ScriptObject;
class ZClassNode;
class NodeEntity;
using namespace Diligent;

const double pi = 3.14159265358979323846;

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

			void WriteScripts(VFile* file);
			void ReadScripts(VFile* file);
			void WriteClass(VFile* file, ZClassNode* cls);
			ZClassNode* ReadClass(VFile* file, ZClassNode* cls);
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

			ScriptObject* AddScript(std::string path, std::string name);

			std::vector<ScriptObject*> GetScripts() {
				return mScriptObjs;
			}
			void SetFilePath(std::string path)
			{
				mPath = path;
			}
			std::string GetFilePath() {
				return mPath;
			}
			void SetScripts(std::vector<ScriptObject*> objs)
			{
				mScriptObjs = objs;
			}


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


			float3* GetPositionPtr() {
				return &mPosition;
			}
		
			float3* GetScalePtr() {
				return &mScale;
			}
			/// <summary>
			/// Sets the name of the node.
			/// </summary>
			/// <param name="name"></param>
			void SetName(std::string name);
			/// <summary>
			/// returns the name of the node.
			/// </summary>
			/// <returns></returns>
			std::string GetName();



			float radians(float degrees)
			{
				return degrees * (pi / 180.0f);
			}

			double radiansToDegrees(double radians)
			{
				return radians * (180.0 / 3.14159265358979323846);
			}

			void SetRotationEular(float3 angles)
			{
				auto cs = &mRotationEular;

				cs[0] = angles;
				
				float sinPitch = std::sin(radians(angles.x));
				float cosPitch = std::cos(radians(angles.x));
				float sinYaw = std::sin(radians(angles.y));
				float cosYaw = std::cos(radians(angles.y));
				float sinRoll = std::sin(radians(angles.z));
				float cosRoll = std::cos(radians(angles.z));

				float4x4 matrix;
				matrix._11 = cosYaw * cosRoll;
				matrix._12 = sinPitch * sinYaw * cosRoll - cosPitch * sinRoll;
				matrix._13 = cosPitch * sinYaw * cosRoll + sinPitch * sinRoll;
				matrix._14 = 0.0f;

				matrix._21 = cosYaw * sinRoll;
				matrix._22 = sinPitch * sinYaw * sinRoll + cosPitch * cosRoll;
				matrix._23 = cosPitch * sinYaw * sinRoll - sinPitch * cosRoll;
				matrix._24 = 0.0f;

				matrix._31 = -sinYaw;
				matrix._32 = sinPitch * cosYaw;
				matrix._33 = cosPitch * cosYaw;
				matrix._34 = 0.0f;

				matrix._41 = 0.0f;
				matrix._42 = 0.0f;
				matrix._43 = 0.0f;
				matrix._44 = 1.0f;

				mRotation = matrix;

			}

			float3* GetRotationEularPtr() {


				float3 result;
				auto matrix = mRotation;
				// Extract the pitch angle
				float3 forward = normalize(float3(matrix._13, matrix._23, matrix._33));
				float pitch = std::atan2(-forward.y, forward.z);
				result[0] = pitch;

				// Extract the yaw angle
				float3 right = normalize(float3(matrix._11, matrix._21, matrix._31));
				float yaw = std::atan2(right.x, std::sqrt(right.y * right.y + right.z * right.z));
				result[1] = yaw;

				// Extract the roll angle
				float3 up = normalize(float3(matrix._12, matrix._22, matrix._32));
				float roll = std::atan2(up.y, up.x);
				result[2] = roll;

				auto cs = &mRotationEular;
				cs[0] = result;
				return &mRotationEular;

			}

			float3 matrixToEulerAngles(const float4x4& matrix)
			{
				float3 result;

				// Extract the pitch angle
				float forwardY = -matrix._31;
				float forwardZ = matrix._21;
				result.x = std::atan2(forwardY, forwardZ);
				result.x = radiansToDegrees(result.x);
				if (result.x < 0)
				{
					result.x += 360.0f;
				}

				// Extract the yaw angle
				float forwardX = matrix._32;
				float yaw = std::atan2(forwardX, forwardZ);
				result.y = radiansToDegrees(yaw);
				if (result.y < 0)
				{
					result.y += 360.0f;
				}

				// Extract the roll angle
				float rightX = matrix._11;
				float upY = matrix._22;
				float roll = std::atan2(rightX, upY);
				result.z = radiansToDegrees(roll);
				if (result.z < 0)
				{
					result.z += 360.0f;
				}

				return result;
			}



			float3 GetRotationEular() {

				return matrixToEulerAngles(mRotation);

			}

			void SetHidden(bool hidden);

			bool IsHidden();

			void BeginNode();
			void EndNode();
			static void AddSystemFunctions();

			virtual void ReadNode(VFile* file, bool read_type = true) {};


			//void WriteScripts(VFile* file);
			//void ReadScripts(VFile* file);

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

			Node3D* GetParent();
			void SetParent(Node3D* parent);



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
			float3 mRotationEular;

			float4x4 mValidTransform;

			//name
			std::string mName;

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
			std::vector<std::string> mScripts;
			std::vector<ScriptObject*> mScriptObjs;


		}
		;

