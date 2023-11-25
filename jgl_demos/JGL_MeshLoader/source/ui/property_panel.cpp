#include "pch.h"
#include "property_panel.h"

namespace nui
{
  void Property_Panel::render(nui::SceneView* scene_view)
  {
    auto mesh = scene_view->get_mesh();

    ImGui::Begin("Properties");
    if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
    {
      
      if (ImGui::Button("Open Mesh"))
      {
        mFileDialog_Mesh.Open();
      }
      ImGui::SameLine(0, 5.0f);
      ImGui::Text(mCurrentFile_Mesh.c_str());
    }

    if (ImGui::CollapsingHeader("Texture", ImGuiTreeNodeFlags_DefaultOpen))
    {
      if (ImGui::Button("Open Tex"))
      {
        mFileDialog_Texture.Open();
      }
      ImGui::SameLine(0, 5.0f);
      ImGui::Text(mCurrentFile_Texture.c_str());
    }
    
    if (ImGui::CollapsingHeader("Material") && mesh)
    {
      ImGui::ColorPicker3("MeshColor", (float*)&mesh->mColor, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
      ImGui::SliderFloat("Roughness", &mesh->mRoughness, 0.0f, 1.0f);
      ImGui::SliderFloat("Metallic", &mesh->mMetallic, 0.0f, 1.0f);
      ImGui::SliderFloat("AO", &mesh->mAO, 0.0f, 1.0f);
    }

    if (ImGui::CollapsingHeader("Light"))
    {
      auto light = scene_view->get_light();
      ImGui::Separator();
      ImGui::Text("Position");
      ImGui::Separator();
      nimgui::draw_vec3_widget("Position", light->mPosition, 80.0f);
      
      ImGui::Separator();
      ImGui::Text("Color");
      ImGui::Separator();
      ImGui::ColorPicker3("LightColor", (float*)&light->mColor, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);

      ImGui::Separator();
      ImGui::Text("Strength");
      ImGui::Separator();
      ImGui::SliderFloat("Strength", &light->mStrength, 0.0f, 100.0f);
    }
  
    //Post Processing
    if (ImGui::CollapsingHeader("Post Processing"))
    {

    }

    //Shader
    if (ImGui::CollapsingHeader("Shader"))
    {
        static int shaderType = ShaderType::Phong;
        ImGui::RadioButton("Phong", &shaderType, 0);
        ImGui::RadioButton("PBR", &shaderType, 1);
        ImGui::RadioButton("BlingPhong_NormalMapping", &shaderType, 2);

        scene_view->SetCurShader(shaderType);
    }
    
    ImGui::End();

    mFileDialog_Mesh.Display();
    if (mFileDialog_Mesh.HasSelected())
    {
      auto file_path = mFileDialog_Mesh.GetSelected().string();
      mCurrentFile_Mesh = file_path.substr(file_path.find_last_of("/\\") + 1);

      mMeshLoadCallback(file_path);

      mFileDialog_Mesh.ClearSelected();
    }

    mFileDialog_Texture.Display();
    if (mFileDialog_Texture.HasSelected())
    {
      auto file_path = mFileDialog_Texture.GetSelected().string();
      mCurrentFile_Texture = file_path.substr(file_path.find_last_of("/\\") + 1);

      mTextureLoadCallback(file_path);

      mFileDialog_Texture.ClearSelected();
    }
    
  }
}
