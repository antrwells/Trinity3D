#pragma once
#ifndef PLATFORM_WIN32
#    define PLATFORM_WIN32 1
#endif

#ifndef ENGINE_DLL
#    define ENGINE_DLL 1
#endif

#ifndef D3D11_SUPPORTED
#    define D3D11_SUPPORTED 1
#endif

#ifndef D3D12_SUPPORTED
#    define D3D12_SUPPORTED 1
#endif

#ifndef GL_SUPPORTED
#    define GL_SUPPORTED 1
#endif

#ifndef VULKAN_SUPPORTED
#    define VULKAN_SUPPORTED 1
#endif
#include "Graphics/GraphicsEngineD3D11/interface/EngineFactoryD3D11.h"
#include "Graphics/GraphicsEngineD3D12/interface/EngineFactoryD3D12.h"
#include "Graphics/GraphicsEngineOpenGL/interface/EngineFactoryOpenGL.h"
#include "Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h"

#include "Graphics/GraphicsEngine/interface/RenderDevice.h"
#include "Graphics/GraphicsEngine/interface/DeviceContext.h"
#include "Graphics/GraphicsEngine/interface/SwapChain.h"
#include "Graphics/GraphicsTools/interface/MapHelper.hpp"
#include "Common/interface/RefCntAutoPtr.hpp"
#include "Graphics/GraphicsTools/interface/GraphicsUtilities.h"
#include "Graphics/GraphicsEngine/interface/GraphicsTypesX.hpp"
#include "Graphics/GraphicsTools/interface/ShaderMacroHelper.hpp"
#include "Graphics/GraphicsTools/interface/MapHelper.hpp"
#

#include "Common/interface/BasicMath.hpp"

namespace HLSL
{
#include "structures.fxh"
}

class BigBuffer;
class SceneGraph;
class Mesh3D;
class SmartDraw;
class Texture2D;

using namespace Diligent;


struct SceneInfo {

	uint num_lights = 0;
	float3 lightPos[32];
	float3 lightDiff[32];
	float3 lightSpec[32];
	float lightRange[32];
	float3 camPos;
	float camMinZ;
	float camMaxZ;
	float4   CameraPos;
	float4x4 InvViewProj;
	uint maxRecursion;
	uint ShadowPCF;
	float4  DiscPoints[8]; // packed float2[16]

};

class SceneRayTracer
{
public:

	SceneRayTracer(SceneGraph* graph);
	void Initialize();
	void ProcessScene();
	void CreatePSO();
	void CreateBindingTables();
	void Render();
	void MapTextures();
	void UpdateConstants();
	void UpdateAttribs();
	void UpdateSceneInfo();

private:
	Uint32          m_MaxRecursionDepth = 8;
	RefCntAutoPtr<IPipelineState>         m_pRayTracingPSO;
	RefCntAutoPtr<IShaderResourceBinding> m_pRayTracingSRB;
	RefCntAutoPtr<IBuffer> m_ConstantsCB;

	int mNumTextures = 8;
	SceneGraph* mGraph;	
	RefCntAutoPtr<IShaderBindingTable> m_pSBT;
	RefCntAutoPtr<ITexture> m_pColorRT;
	RefCntAutoPtr<ITextureView> m_pColorRTV;
	RefCntAutoPtr<ITextureView> m_pColorRTVRT;
	TEXTURE_FORMAT          m_ColorBufferFormat = TEX_FORMAT_RGBA32_FLOAT;
	HLSL::Constants m_Constants = {};
	bool mUpdateAttribs = true;
	RefCntAutoPtr<IBuffer> m_CubeAttribsCB;
	std::vector<Mesh3D*> mInstanceGeos;
	Texture2D* mColorTex;
	SmartDraw* mDraw;
	BigBuffer* mBigBuffer;
	bool mSetBB = false;
	bool mCreatedSceneInfo = false;
	RefCntAutoPtr<IBuffer> mSceneInfoBuffer;
	RefCntAutoPtr<IBufferView> mSceneInfoBufferView;
	SceneInfo mSceneInfo;

};



