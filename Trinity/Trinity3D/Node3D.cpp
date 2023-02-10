#include "pch.h"
#include "Node3D.h"
#ifndef PLATFORM_WIN32
#    define PLATFORM_WIN32 1
#endif

//#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtx/transform.hpp"
#include "Maths.h"
//#include "VarTypes.h"



bool Node3D::mSysInit = false;

NodeType Node3D::GetType() {

	return mType;

}

float3x3 Node3D::GetRotation() {

	auto r1 = mRotation[0];
	auto r2 = mRotation[1];
	auto r3 = mRotation[2];

	float3 row1(r1[0], r1[1], r1[2]);
	float3 row2(r2[0], r2[1], r2[2]);
	float3 row3(r3[0], r3[1], r3[2]);


	return float3x3(row1, row2, row3);

}

void Node3D::SetRotation3x3(float3x3 rot) {

	mRotation[0][0] = rot[0][0];
	mRotation[0][1] = rot[0][1];
	mRotation[0][2] = rot[0][2];

	mRotation[1][0] = rot[1][0];
	mRotation[1][1] = rot[1][1];
	mRotation[1][2] = rot[1][2];

	mRotation[2][0] = rot[2][0];
	mRotation[2][1] = rot[2][1];
	mRotation[2][2] = rot[2][2];

}

Node3D* Node3D::FindNode(std::string name) {

	if (std::string(mName) == name)
	{
		return this;
	}
	for (int i = 0; i < mChildren.size(); i++)
	{

		auto res = mChildren[i]->FindNode(name);
		if (res != nullptr) {
			return res;
		}

	}
	return nullptr;
}

float4x4 Node3D::GetRotation4x4() {

	return mRotation;

}


 void Node3D::Render() {
	RenderChildren();
};//overriden usually to render nodes onto the framebuffer.
/// <summary>
/// Internal use.
/// </summary>
 void Node3D::RenderDepth() {
	RenderDepthChildren();
}
/// <summary>
/// Internal use.
/// </summary>
void Node3D::RenderChildren() {
	for (int i = 0; i < mChildren.size(); i++) {

		auto child = mChildren[i];
		if (child->GetEnabled() == false) continue;
		child->Render();

	}
}

/// </summary>
void Node3D::RenderDepthChildren() {

	for (int i = 0; i < mChildren.size(); i++) {

		auto child = mChildren[i];
		if (child->GetEnabled() == false) continue;
		child->RenderDepth();

	}

}

float3 Node3D::GetScale() {
	return mScale;
}

void Node3D::SetRotation(float4x4 mat) {

	mRotation = mat;
	//mChanged = true;
	//SetChanged();


	//InvalidateTransform();

}

size_t Node3D::ChildrenCount() {
	return mChildren.size();
}


Node3D* Node3D::GetChild(int id) {
	return mChildren[id];
}


Node3D* Node3D::GetRootNode() {
	return mRootNode;
}


float3 Node3D::GetPositionWorld() {

	//return float4x4::Translation(0,0,0)* GetWorldMatrix();

	return float3(0, 0, 0) * GetWorldMatrix();
}

void Node3D::RemoveNode(Node3D* node) {

	std::vector<Node3D*> new_list;
	for (int i = 0; i < mChildren.size(); i++) {

		if (mChildren[i] == node) {

		}
		else {
			new_list.push_back(mChildren[i]);
		}

	}
	mChildren = new_list;

}


void Node3D::SetHidden(bool hidden) {
	mHidden = hidden;
}

bool Node3D::IsHidden() {
	return mHidden;
}


void Node3D:: SetEnabled(bool enable) {
	mEnabled = enable;
}

bool Node3D::GetEnabled() {
	return mEnabled;
}

void Node3D::ClearNodes() {

	mChildren.resize(0);

}

bool Node3D::IsPlaying() {
	return mPlaying;
}
void Node3D::SetPlaying(bool play) {
	mPlaying = play;
}

	Node3D::Node3D() {

		mRotation = float4x4::Identity();

		//mRotation = glm::mat4(1.0f);
		mName = "Root";
		mPosition = float3(0, 0, 0);
		mScale = float3(1, 1, 1);
		//mComponents.resize(0);
		mType = NodeType::Node;
		if (mSysInit == false) {
		//	AddSystemFunctions();
		//	mSysInit = true;
		}
		mChanged = true;
		//SetChanged();
		mEnabled = true;
		

	}

	void Node3D::RenderUI() {

	

	}

	void Node3D::Update() {

		if (mEnabled == false) return;
	


		//UpdateComponents();

		UpdateChildren();

		UpdateActor();
	}

	



	void Node3D::UpdateChildren() {
		if (mEnabled == false) return;
		for (int i = 0; i < mChildren.size(); i++) {

			auto child = mChildren[i];
			child->Update();

		}

	}

	float4x4 Node3D::GetWorldMatrix() {



			float4x4 previous_matrix = float4x4::Identity();
			 
			if (mRootNode != nullptr) {

				previous_matrix = mRootNode->GetWorldMatrix();

			}

			//float4x4 scale_matrix = float4x4::Scale(mScale);
			float4x4 position_matrix;
			float4x4 rot_matrix;
			float4x4 final_matrix;
			float4x4 scale_matrix = float4x4::Scale(mScale);
			if (mType == NodeType::Camera) {

				position_matrix = float4x4::Translation(mPosition).Inverse();
				rot_matrix = mRotation;
				final_matrix = position_matrix * rot_matrix;// *scale_matrix;
			}
			else {
				position_matrix = float4x4::Translation(mPosition);
				rot_matrix = mRotation;
				final_matrix = scale_matrix * rot_matrix * position_matrix;// *scale_matrix;// *scale_matrix;
			}


			 

			


			mValidTransform = previous_matrix * final_matrix;

			mTransformInvalidated = false;

			return  final_matrix * previous_matrix;

		
		

	

	}

	void Node3D::SetRootNode(Node3D* node) {

		mRootNode = node;
		

	}

	void Node3D::AddNode(Node3D* node) {

		if (node->GetRootNode() != nullptr) {
			auto rn = node->GetRootNode();
			rn->RemoveNode(node);
		}
		mChildren.push_back(node);
		node->SetRootNode(this);

	}

	float3 Node3D::GetPosition() {

		return mPosition;

	}

	//Position/Rotation/Scale
	void Node3D::SetPosition(float3 position) {

		mPosition = position;



	}

	void Node3D::SetRotation(float pitch, float yaw, float roll) {

		
		
		pitch = Maths::Deg2Rad(pitch);
		yaw = Maths::Deg2Rad(yaw);
		roll = Maths::Deg2Rad(roll);

		float4x4 pitch_matrix = float4x4::RotationX(pitch);
		float4x4 yaw_matrix = float4x4::RotationY(yaw);
		float4x4 roll_matrix = float4x4::RotationZ(roll);


		mRotation = yaw_matrix * pitch_matrix * roll_matrix;
	//	mRotation = mRotation.Inverse();

		//InvalidateTransform();
	}

	void Node3D::SetScale(float3 scale) {

		mScale = scale;
	
	//	InvalidateTransform();

	}

	void Node3D::Move(float3 move) {

		if (mType == NodeType::Camera)
		{
			float4 mv = mRotation * float4(move, 1.0f);// *mRotation;

			mPosition += float3(mv.x, mv.y, mv.z);
		}
		else {

			float4 mv = float4(move, 1.0f) *mRotation;

			mPosition += float3(mv.x, mv.y, mv.z);

		}

		//InvalidateTransform();
	}


	const char* Node3D::GetName() {
		return mName;
	}

	void Node3D::SetName(const char* name) {

		mName = name;

	}

	void Node3D::RotateLocal(float pitch, float yaw, float roll) {

		pitch = Maths::Deg2Rad(pitch);
		yaw = Maths::Deg2Rad(yaw);
		roll = Maths::Deg2Rad(roll);

		float4x4 pitch_matrix = float4x4::RotationX(pitch);
		float4x4 yaw_matrix = float4x4::RotationY(yaw);
		float4x4 roll_matrix = float4x4::RotationZ(roll);


		mRotation = (yaw_matrix * pitch_matrix * roll_matrix) * mRotation;

	
		UpdateRotation();
	}


	void Node3D::RotateGlobal(float pitch, float yaw, float roll) {

		pitch = Maths::Deg2Rad(pitch);
		yaw = Maths::Deg2Rad(yaw);
		roll = Maths::Deg2Rad(roll);

		float4x4 pitch_matrix = float4x4::RotationX(pitch);
		float4x4 yaw_matrix = float4x4::RotationY(yaw);
		float4x4 roll_matrix = float4x4::RotationZ(roll);


		mRotation = mRotation *(yaw_matrix * pitch_matrix * roll_matrix);


	
		UpdateRotation();
	}

	void Node3D::SetRotation4x4(float4x4 rotation) {

		mRotation = rotation;


	}

	



	void Node3D::BeginNode() {

		if (mEnabled == false) return;
		mPushPos = mPosition;
		mPushRot = mRotation;
		mPushScale = mScale;

	

	}

	void Node3D::EndNode() {
		if (mEnabled == false) return;
		SetPosition(mPushPos);
		SetScale(mPushScale);
		SetRotation(mPushRot);

	
	

	}


