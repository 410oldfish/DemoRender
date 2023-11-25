#pragma once

#include "elems/light.h"
#include "ui/scene_view.h"

#include "imgui.h"
#include "utils/imgui_widgets.h"
#include <ImFileBrowser.h>

namespace nui
{
  class Property_Panel
  {
  public:
    Property_Panel()
    {
      mCurrentFile_Mesh = "< ... >";
      mFileDialog_Mesh.SetTitle("Open mesh");
      mFileDialog_Mesh.SetFileFilters({ ".fbx", ".obj" });

      mCurrentFile_Texture = "< ... >";
      mFileDialog_Texture.SetTitle("Open tex");
      mFileDialog_Texture.SetFileFilters({ ".png", ".jpg", ".tga" });
    }

    void render(nui::SceneView* mScene);

    void set_mesh_load_callback(const std::function<void(const std::string&)>& callback)
    {
      mMeshLoadCallback = callback;
    }

    void set_tex_load_callback(const std::function<void(const std::string&)>& callback)
    {
      mTextureLoadCallback = callback;
    }

    enum ShaderType
    {
      Phong,
      Pbr,
      BlinnPhong_NormalMapping
    };
  private:
    // create a file browser instance
    //Mesh
    ImGui::FileBrowser mFileDialog_Mesh;
    std::string mCurrentFile_Mesh;
    std::function<void(const std::string&)> mMeshLoadCallback;

    //Texture
    ImGui::FileBrowser mFileDialog_Texture;
    std::string mCurrentFile_Texture;
    std::function<void(const std::string&)> mTextureLoadCallback;

  };
}

