#pragma once
//#include "GBuffer.h"

class SmartDraw;

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

#include "Common/interface/BasicMath.hpp"

using namespace Diligent;

class GBuffer;
class SceneGraph;

class SceneRenderer
{
public:

	SceneRenderer(SceneGraph* graph);

	void RenderData(SceneGraph* graph);
	void RenderData();

	//deferred
	void CreateDRPSO();

	//
	void RenderSceneDeferred();

private:

	GBuffer* mGBuffer;
	int mWidth, mHeight;
	SceneGraph* mGraph;
	SmartDraw* mDraw;

	//deferred renderer.
	RefCntAutoPtr<IPipelineState>         m_PSO_DR;
	RefCntAutoPtr<IBuffer> m_DRConstants;
	RefCntAutoPtr<IShaderResourceBinding> m_SRB_DR;
};

