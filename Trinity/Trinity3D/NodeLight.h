#pragma once
#include "Node3D.h"

#include "RenderTargetCube.h"


		enum LightType {
			PointLight, SpotLight, DirectionalLight
		};


		/// <summary>
		/// NodeLight is the general purpose light class. These are used to light the scene, and also for shadow mapping.
		/// </summary>
		class NodeLight : public Node3D
		{
		public:

			static NodeLight* Active;

			/// <summary>
			/// Creates a new light. if shadowFB is true, the light casts shadows, if false, then it does not.
			/// </summary>
			/// <param name="shadowFB"></param>
			NodeLight(bool shadowFB = true);

			/// <summary>
			/// Gets the diffuse color of the light.
			/// </summary>
			/// <returns></returns>
			float3 GetDiffuse() {
				return mDiffuse;
			}

			float3* GetDiffusePtr() {

				return &mDiffuse;

			}

			/// <summary>
			/// Gets the specular color of the light.
			/// </summary>
			/// <returns></returns>
			float3 GetSpecular() {
				return mSpecular;
			}

			float3* GetSpecularPtr() {
				return &mSpecular;
			}

			/// <summary>
			/// Gets the range of the light.
			/// </summary>
			/// <returns></returns>
			float GetRange() {
				return mRange;
			}

			float* GetRangePtr() {
				return &mRange;
			}

			
			/// <summary>
			/// Sets the diffuse color of the light.
			/// </summary>
			/// <param name="diffuse"></param>
			void SetDiffuse(float3 diffuse)
			{
				auto dp = &mDiffuse;
				dp[0] = diffuse;

			}

			/// <summary>
			/// Sets the specular color of the light.
			/// </summary>
			/// <param name="specular"></param>
			void SetSpecular(float3 specular) {

				auto ds = &mSpecular;
				ds[0] = specular;

			}

			/// <summary>
			/// Sets weather the light casts shadows
			/// </summary>
			/// <param name="cast"></param>
			void SetCastShadows(bool cast) {

				auto ls = &mCastShadows;
				ls[0] = cast;

			}

			bool* GetCastShadowsPtr() {
				return &mCastShadows;
			}

			/// <summary>
			/// Returns true if the light casts shadows.
			/// </summary>
			/// <returns></returns>
			bool GetShadowMapping() {

				return mCastShadows;

			}

			bool* GetShadowMappingPtr() {

				return &mCastShadows;

			}

			/// <summary>
			/// Sets the range of the light.
			/// </summary>
			/// <param name="range"></param>
			void SetRange(float range) {

				auto lr = &mRange;
				lr[0] = range;

			}

			static int ShadowMapRes;
			/// <summary>
			/// Internal use.
			/// </summary>
			/// 
			//Kinetic::Framebuffer::FramebufferCube* GetShadowFB() {
			//	return ShadowFB;
			//}

			/// <summary>
			/// if called, the light is removed from the scene as soon as possible.
			/// </summary>
			void QueueRemove() {
				mQueueRemove = true;
			}
			/// <summary>
			/// Internal use.
			/// </summary>
			bool IsQueueRemoved() {

				return mQueueRemove;

			}

			void SetLightType(LightType type) {
				auto lt = &mLightType;
				lt[0] = type;
			}
			LightType GetLightType() {
				return mLightType;
			}

			LightType* GetLightTypePtr() {
				return &mLightType;
			}



			float3 GetCone() {
				return float3(mICone, mOCone, 0);
			}
			void SetCone(float3 cone)
			{
				mICone = cone.x;
				mOCone = cone.y;
			}

			RenderTargetCube* GetShadowCube() {
				return mShadowCube;
			}

			bool GetCastShadows() {
				
				return mCastShadows;
			}

		private:

			float mRange = 40;

			float3 mDiffuse;
			float3 mSpecular;
			float3 mAmbient;

			bool mCastShadows = true;
			//Kinetic::Framebuffer::FramebufferCube* ShadowFB;
			bool mQueueRemove = false;
			RenderTargetCube* mShadowCube = nullptr;
			LightType mLightType = PointLight;
			float mICone, mOCone;

		};



	