#include "pch.h"
#include "Texture2D.h"
#include "TrinityApp.h"




        Texture2D::Texture2D(const char* path, bool alpha) {

            for (int i = 0; i < mCache.size(); i++) {

                auto ct = mCache[i];
                if (ct->GetPath() == std::string(path))
                {

                    m_TextureSRV = ct->GetView();
                    Texture = ct->GetTexture();
                    mPath = ct->GetPath();
                    return;

                }

            }

            auto m_pDevice = TrinityApp::GetDev();
            TextureLoadInfo loadInfo;
            loadInfo.IsSRGB = false;
            if (alpha) {
                //   loadInfo.Format = TEX_FORMAT_RGBA8_UINT;
            }
            //loadInfo.AlphaCutoff = 0.1f;


            RefCntAutoPtr<ITexture> Tex;
            CreateTextureFromFile(path, loadInfo, m_pDevice, &Tex);
            //  Get shader resource view from the texture
            m_TextureSRV = Tex->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);
            Texture = Tex;
            mPath = std::string(path);
            mCache.push_back(this);

        }

        Texture2D::Texture2D(RefCntAutoPtr<ITexture> texture, RefCntAutoPtr<ITextureView> view)
        {

            Texture = texture;
            m_TextureSRV = view;

        }

        Texture2D::Texture2D(RefCntAutoPtr<ITexture> texture)
        {

            Texture = texture;
            m_TextureSRV = Texture->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);
        }

        /*
        Texture2D::Texture2D(Application* app,int w, int h, bool alpha,const char* buf) {

            TextureDesc TexDesc;
            TexDesc.Type = RESOURCE_DIM_TEX_2D;
            TexDesc.Format = TEX_FORMAT_RGBA8_UNORM_SRGB;
            TexDesc.Width = w;
            TexDesc.Height = h;
            TexDesc.MipLevels = 1;
            TexDesc.BindFlags = BIND_SHADER_RESOURCE;
            TexDesc.Usage = USAGE_DEFAULT;

            mWidth = w;
            mHeight = h;

            TextureSubResData data;
            data.pData = buf;
            data.Stride = w * 4;

            TextureData InitData;
            // Pointer to subresouce data, one for every mip level
            InitData.pSubResources = &data;
            InitData.NumSubresources = 1;

            app->GetDevice()->CreateTexture(TexDesc, &InitData, &Texture);
            m_TextureSRV = Texture->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);

        }


        Texture2D::Texture2D(RenderTarget2D* target) {

            Texture = target->GetColorTexture();
            m_TextureSRV = target->GetColorTexture()->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);

        }
        */


        void Texture2D::Free() {

            Texture->Release();
            Texture.Detach();

            //Texture.Release();
            m_TextureSRV->Release();
            m_TextureSRV.Detach();

        }

        /*
        Texture2D::Texture2D(RenderTargetCube* target, int face)
        {
            Texture = target->GetColorTexture();
            m_TextureSRV = target->GetColorViewFace(face);
        }
        */

        std::vector<Texture2D*> Texture2D::mCache;

