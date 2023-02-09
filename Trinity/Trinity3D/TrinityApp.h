#pragma once
#include <Windows.h>


#ifndef PLATFORM_WIN32
#    define PLATFORM_WIN32 1
#endif

#ifndef ENGINE_DLL
#    define ENGINE_DLL 1
#endif

#ifndef D3D12_SUPPORTED
#    define D3D12_SUPPORTED 1
#endif


#include "Graphics/GraphicsEngineD3D12/interface/EngineFactoryD3D12.h"


#include "Graphics/GraphicsEngine/interface/RenderDevice.h"
#include "Graphics/GraphicsEngine/interface/DeviceContext.h"
#include "Graphics/GraphicsEngine/interface/SwapChain.h"

#include "Common/interface/RefCntAutoPtr.hpp"

#include "Common/interface/BasicMath.hpp"

using namespace Diligent;


#include <d3d12.h>

class TrinityApp
{
public:

	TrinityApp(HWND window);
    void DoFrame();
    void Resize(int w, int h);

    static RefCntAutoPtr<IRenderDevice> GetDev() {
        return s_pThis->GetDevice();
    }
    RefCntAutoPtr<IRenderDevice> GetDevice() {

        return m_pDevice;

    }
    static TrinityApp* s_pThis;
private:

	HWND mWindow;
    bool mResized = false;
    RefCntAutoPtr<IRenderDevice>  m_pDevice;
    RefCntAutoPtr<IDeviceContext> m_pImmediateContext;
    RefCntAutoPtr<ISwapChain>     m_pSwapChain;
    RefCntAutoPtr<IPipelineState> m_pPSO;
    RefCntAutoPtr<IEngineFactory> m_pEngFac;
    RENDER_DEVICE_TYPE            m_DeviceType = RENDER_DEVICE_TYPE_D3D12;

};

