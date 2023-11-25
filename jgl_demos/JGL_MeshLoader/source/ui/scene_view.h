#pragma once

#include "elems/camera.h"
#include "elems/mesh.h"
#include "elems/light.h"
#include "shader/shader_util.h"
#include "render/opengl_buffer_manager.h"
#include "elems/input.h"
#include "elems/texture.h"

namespace nui
{
  class SceneView
  {
  public:
    SceneView() : 
      mCamera(nullptr), mFrameBuffer(nullptr), mShader_Phong(nullptr),
      mLight(nullptr), mSize(800, 600)
    {
      mFrameBuffer = std::make_unique<nrender::OpenGL_FrameBuffer>();
      mFrameBuffer->create_buffers(800, 600);
      //All Shader Init
      mShader_Phong = std::make_shared<nshaders::Shader>();
      mShader_Pbr = std::make_shared<nshaders::Shader>();
      load_shader();
      SetCurShader(mShader_Phong);//default Phong
      mLight = std::make_unique<nelems::Light>();

      mCamera = std::make_unique<nelems::Camera>(glm::vec3(0, 0, 3), 45.0f, 1.3f, 0.1f, 100.0f);
    }

    ~SceneView()
    {
      mShader_Phong->unload();
    }

    nelems::Light* get_light() { return mLight.get(); }

    void resize(int32_t width, int32_t height);


    void render();

    void load_mesh(const std::string& filepath);

    void set_mesh(std::shared_ptr<nelems::Mesh> mesh)
    {
      mMesh = mesh;
    }

    std::shared_ptr<nelems::Mesh> get_mesh() { return mMesh; }
    
    void on_mouse_move(double x, double y, nelems::EInputButton button);

    void on_mouse_wheel(double delta);

    void on_keyboard_forward_move(float dir);

    void on_keyboard_right_move(float dir);
    
    void reset_view()
    {
      mCamera->reset();
    }

    void load_shader()
    {
        mShader_Phong->load("shaders/vs.shader", "shaders/fs.shader");
        mShader_Pbr->load("shaders/vs.shader", "shaders/fs_pbr.shader");
        mShader_BlingPhong_NormalMapping->load("shaders/vs_normalMapping.shader", "shaders/fs_normalMapping.shader");
    }

    void load_texture(const std::string& filepath);

    void SetCurShader(std::shared_ptr<nshaders::Shader> shader)
    {
        mCurShader = shader;
    }

    void SetCurShader(int shaderType)
    {
        switch (shaderType)
        {
          case 0:
            SetCurShader(mShader_Phong);
            break;
          case 1:
            SetCurShader(mShader_Pbr);
            break;
          case 2:
            SetCurShader(mShader_BlingPhong_NormalMapping);
            break;
        }
    }

    void UseCurShader()
    {
        mCurShader->use();
    }
    
  private:
    std::unique_ptr<nelems::Camera> mCamera;
    std::unique_ptr<nrender::OpenGL_FrameBuffer> mFrameBuffer;
    int curShaderProgramId = 0;
    std::shared_ptr<nshaders::Shader> mCurShader;
    std::shared_ptr<nshaders::Shader> mShader_Phong;
    std::shared_ptr<nshaders::Shader> mShader_Pbr;
    std::shared_ptr<nshaders::Shader> mShader_BlingPhong_NormalMapping;
    std::unique_ptr<nelems::Light> mLight;
    std::shared_ptr<nelems::Mesh> mMesh;
    std::shared_ptr<nelems::Texture> mTexture_Diff;//漫反射
    std::shared_ptr<nelems::Texture> mTexture_Normal_Tangent;//切线空间法线贴图
    std::shared_ptr<nelems::Texture> mTexture_Specular;//镜面反射
    std::shared_ptr<nelems::Texture> mTexture_Glow;//发光补充
    glm::vec2 mSize;
  };
}

