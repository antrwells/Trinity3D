#include "TrinityApp.h"



        TrinityApp* TrinityApp::s_pThis = nullptr;

        TrinityApp::TrinityApp(HWND window)
        {

            mWindow = window;

            SwapChainDesc SCDesc;
            SCDesc.ColorBufferFormat = TEX_FORMAT_RGBA8_UNORM;
            SCDesc.DepthBufferFormat = TEX_FORMAT_D16_UNORM;

#   if ENGINE_DLL
            // Load the dll and import GetEngineFactoryD3D12() function
            auto GetEngineFactoryD3D12 = LoadGraphicsEngineD3D12();
#    endif
            EngineD3D12CreateInfo EngineCI;
            EngineCI.Features.RayTracing = DEVICE_FEATURE_STATE_ENABLED;
            auto* pFactoryD3D12 = GetEngineFactoryD3D12();
            pFactoryD3D12->CreateDeviceAndContextsD3D12(EngineCI, &m_pDevice, &m_pImmediateContext);
            Win32NativeWindow Window{ mWindow };
            pFactoryD3D12->CreateSwapChainD3D12(m_pDevice, m_pImmediateContext, SCDesc, FullScreenModeDesc{}, Window, &m_pSwapChain);
            m_pEngFac = pFactoryD3D12;
            s_pThis = this;
        }

        void TrinityApp::DoFrame() {

            auto* pRTV = m_pSwapChain->GetCurrentBackBufferRTV();
            auto* pDSV = m_pSwapChain->GetDepthBufferDSV();
            m_pImmediateContext->SetRenderTargets(1, &pRTV, pDSV, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

            // Clear the back buffer
            const float ClearColor[] = { 1,0,0, 0.0f };
            // Let the engine perform required state transitions
            m_pImmediateContext->ClearRenderTarget(pRTV, ClearColor, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
            m_pImmediateContext->ClearDepthStencil(pDSV, CLEAR_DEPTH_FLAG, 1.f, 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

            // RenderApp();

            m_pImmediateContext->SetRenderTargets(1, &pRTV, pDSV, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);


        }

        void TrinityApp::Resize(int w, int h)
        {

            if (m_pSwapChain)
                m_pSwapChain->Resize(w, h);
            // winWidth = width;
            // winHeight = height;
            auto SC = m_pSwapChain->GetDesc();
            m_Width = w;
            m_Height = h;
            //m_pImGui.reset(new ImGuiImplWin32(curWin, m_pDevice, SC.ColorBufferFormat, SC.DepthBufferFormat));
            mResized = true;
        }

