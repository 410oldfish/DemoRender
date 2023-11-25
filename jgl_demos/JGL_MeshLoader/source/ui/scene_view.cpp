#include "pch.h"
#include "scene_view.h"

#include "imgui.h"

namespace nui
{
  void SceneView::resize(int32_t width, int32_t height)
  {
    mSize.x = width;
    mSize.y = height;

    mFrameBuffer->create_buffers((int32_t)mSize.x, (int32_t) mSize.y);
  }

  void SceneView::on_mouse_move(double x, double y, nelems::EInputButton button)
  {
    mCamera->on_mouse_move(x, y, button);
  }

  void SceneView::on_mouse_wheel(double delta)
  {
    mCamera->on_mouse_wheel(delta);
  }

  void SceneView::on_keyboard_forward_move(float dir)
  {
    mCamera->move_forward(dir);
  }
  void SceneView::on_keyboard_right_move(float dir)
  {
    mCamera->move_right(dir);
  }
  
  void SceneView::load_mesh(const std::string& filepath)
  {
    if(!mMesh)
      mMesh = std::make_shared<nelems::Mesh>();
    
    mMesh->load(filepath);
  }

  void SceneView::load_texture(const std::string& filepath)
  {
    if (!mTexture_Diff)
      mTexture_Diff = std::make_shared<nelems::Texture>(filepath);
  }

  void SceneView::render()
  {
    //设置渲染Shader方案
    UseCurShader();//glUseProgram

    mLight->update(mCurShader.get());

    mFrameBuffer->bind();

    if (mMesh)//如果有选中的mesh
    {
      mTexture_Diff->update(mCurShader.get(), "diffuseMap");
      mTexture_Diff->UseTex();
      
      mMesh->update(mCurShader.get());//更新shader中的uniform变量
      mMesh->render();//渲染
    }

    mFrameBuffer->unbind();//解绑framebuffer，这一帧的渲染已经写入到framebuffer中了

    ImGui::Begin("Scene");

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    mSize = { viewportPanelSize.x, viewportPanelSize.y };

    mCamera->set_aspect(mSize.x / mSize.y);
    mCamera->update(mCurShader.get());//这里更新的是shader的mvp

    // add rendered texture to ImGUI scene window
    uint64_t textureID = mFrameBuffer->get_texture();
    ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ mSize.x, mSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
    /*  这里有一个坐标系转换
     *  OpenGL的坐标系是左下角为原点，右上角为最大值
     * y^
     *  |
     *  |
     *  | 
     *  |_______>
     * (0,0)     x
     *
     *  Imgui的坐标系是左上角为原点，右下角为最大值
     * (0,0)            x
     *  ---------------->
     * |
     * |
     * |
     * |
     * v
     * y
     * 
     */
    ImGui::End();
  }
}
