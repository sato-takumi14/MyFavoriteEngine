#include  "main.h"
#include "renderer.h"
#include "imgui_impl_dx11.h"
#include "guiProject.h"
#include "dropFile.h"

void GuiProject::Init()
{

}

void GuiProject::Uninit()
{

}

void GuiProject::Update()
{

}

void GuiProject::Draw()
{
    ImGui::Begin("Project", 0);

    //static const char* a = nullptr;


    //ルートオブジェクトを表示
   /* if(DropFile::DropFileData())
    ImGui::Selectable(DropFile::DropFileData());*/

    ImGui::End();
}
