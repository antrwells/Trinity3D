#include "pch.h"
#include "NodeCamera.h"

#include "Maths.h"
#include "TrinityApp.h"
#include "Texture2D.h"




		/// <summary>
		/// How close to 0 a point in the render can happen.
		/// </summary>
		/// <returns></returns>
		float NodeCamera::GetMinZ() {
			return mMinZ;
		}

		/// <summary>
		/// How far into the distance the camera can see.
		/// </summary>
		/// <returns></returns>
		float NodeCamera::GetMaxZ() {
			return mMaxZ;
		}

		/// <summary>
		/// Set the minimum distance of the render.
		/// </summary>
		/// <param name="z"></param>
		void NodeCamera::SetMinZ(float z) {
			mMinZ = z;
		}

		void NodeCamera::SetMaxZ(float z) {
			mMaxZ = z;
			SetViewport(0, 0, (int)mWidth, (int)mHeight);
		}

		void NodeCamera::SetFOV(float fov)
		{
			mFOV = fov;
			SetViewport(0, 0, (int)mWidth, (int)mHeight);
		}

		float NodeCamera::GetFOV()
		{
			return mFOV;
		}

		float4x4 NodeCamera::GetWorldMatrixNoInvert() {

			return Node3D::GetWorldMatrix();

		}


		NodeCamera::NodeCamera() {

			//		mProjectionMatrix = 
			SetViewport(0, 0, TrinityApp::GetApp()->GetWidth(), TrinityApp::GetApp()->GetHeight());
			mType = NodeType::Camera;
			mName = "Game Camera";
			//if (mLensDefualt == nullptr) {
			//	mLensDefualt = new Texture2D("data/lensImage.png");
			//}
		//	mLensImage = mLensDefualt;
		}

		

		void NodeCamera::SetViewport(int x, int y, int w, int h) {

			//***

			mProjectionMatrix = float4x4::Projection(Maths::Deg2Rad(mFOV), (float)(w) / (float)(h), mMinZ, mMaxZ, false);
		

			//float nv = Kinetic::Maths::Deg2Rad(mFOV);
			//mProjectionMatrix = glm::perspective<float>(nv, (float)w / (float)h, mMinZ, mMaxZ);
			mWidth = (float)w;
			mHeight = (float)h;
			//mProj = glm::perspectiveFov(FOV, (float)w, (float)h, minZ, maxZ);


		}


		float4x4 NodeCamera::GetWorldMatrix() {

			float4x4 world_matrix = Node3D::GetWorldMatrix();

			return world_matrix.Inverse();

		}

		float4x4 NodeCamera::GetProjectionMatrix() {

			return mProjectionMatrix;

		}
