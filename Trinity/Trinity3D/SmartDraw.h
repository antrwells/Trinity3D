#pragma once





#ifndef PLATFORM_WIN32
#    define PLATFORM_WIN32 1
#endif


#include "Graphics/GraphicsEngineD3D12/interface/EngineFactoryD3D12.h"


#include "Graphics/GraphicsEngine/interface/RenderDevice.h"
#include "Graphics/GraphicsEngine/interface/DeviceContext.h"
#include "Graphics/GraphicsEngine/interface/SwapChain.h"
#include "Graphics/GraphicsTools/interface/MapHelper.hpp"
#include "Common/interface/RefCntAutoPtr.hpp"
#include "Graphics/GraphicsTools/interface/GraphicsUtilities.h"
#include "TrinityApp.h"
#include "Texture2D.h"

//#include "Common/interface/BasicMath.hpp"


using namespace Diligent;

namespace Trinity {
	namespace Draw {

		struct DrawInfo {

			float x[4];
			float y[4];
			float z = 0;
			bool flip_uv = false;
			Trinity::Texture::Texture2D* Tex = nullptr;
			//Kinetic::Textures::Texture2D* Norm;
			float r = 0, g = 0, b = 0, a = 0;


		};

		/// <summary>
		/// Internal use.
		/// </summary>
		struct DrawList {

			std::vector<DrawInfo*> Draws;
			Trinity::Texture::Texture2D* Tex = nullptr;
			//Kinetic::Textures::Texture2D* Norm;


		};

		struct Vertex2D
		{
			float3 pos;
			float4 color;
			float2 uv;
		};


		class SmartDraw
		{
		public:

			SmartDraw(App::TrinityApp* app);
			void CreateVertexBuffer(DrawList* list);
			void CreateIndexBuffer(DrawList* list);

			void Begin();
			void DrawQuad(int x, int y, int w, int h, float r, float g, float b, float a);
			void DrawTexture(int x, int y, int w, int h, Trinity::Texture::Texture2D* tex, float r, float g, float b, float a, bool flip_uv = false);
			void End(RefCntAutoPtr<IPipelineState> pso, RefCntAutoPtr<IBuffer> consts, RefCntAutoPtr<IShaderResourceBinding> srb);
			void End();
			void End(float4x4 proj);
			DrawList* GetDrawList(Trinity::Texture::Texture2D* tex) {

				for (int i = 0; i < Draws.size(); i++) {

					DrawList* l = Draws[i];
					if (l->Tex == tex) {

						return l;

					}

				};

				DrawList* l = new DrawList;
				l->Tex = tex;
				//l->Norm = NULL;
				Draws.push_back(l);
				return l;

			};
			//DrawList* GetDrawList(Kinetic::Textures::Texture2D* tex);



		private:
			App::TrinityApp* gApp;
			std::vector<DrawList*> Draws;
			float drawZ = 1.0f;
			RefCntAutoPtr<IPipelineState>         m_pPSO;
			RefCntAutoPtr<IBuffer>                m_VSConstants;
			RefCntAutoPtr<IShaderResourceBinding> m_pSRB;
			float4x4                              m_Proj;
			RefCntAutoPtr<IBuffer>                m_CubeVertexBuffer;
			RefCntAutoPtr<IBuffer>                m_CubeIndexBuffer;
			float cZ = 0.0;
			bool made = false;
			Vertex2D* vertices;
			Uint32* indices;
		};

	}

}