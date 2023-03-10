#pragma once
#include <ctype.h>
#ifndef PLATFORM_WIN32
#    define PLATFORM_WIN32 1
#endif
#include "PxPhysicsAPI.h"
#include "Physics.h"

#include "Common/interface/BasicMath.hpp"

using namespace Diligent;


	class PhysicsBody
	{
	public:

		virtual void InitBody() {};

		float3 GetPosition();
		float4x4 GetRotation();
		void SetRotation(float3x3 rotation);
		void SetPosition(float3 pos);
		void SetConstraint(bool x, bool y, bool z);
		void Turn(float x, float y, float z);
		void SetAngularForce(float x, float y, float z);
		void ApplyForce(float x, float y, float z);
		void ApplyLocalForce(float x, float y, float z);
		void SetForce(float x, float y, float z);
		void SetLocalForce(float x, float y, float z);
		void AddLocalForce(float x, float y, float z, float dampen);
		float3 GetForce();
		float GetRotationY();
		void RemoveStatic() {
			
			
		}
		void RemoveDynamic() {
			
		}
		void Remove() {
			if (body != nullptr) {
				Physics::Main->Remove(body);
			}
			if (sbody != nullptr) {
				Physics::Main->RemoveStatic(sbody);
			}
		}
	protected:
		physx::PxRigidDynamic* body = nullptr;
		physx::PxRigidStatic* sbody = nullptr;
		bool mHere = false;
		physx::PxShape* shape;
		physx::PxMaterial* material;
		float w=0, h=0, d=0;
	};
