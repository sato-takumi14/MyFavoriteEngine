#include  "main.h"
#include "renderer.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "input.h"
#include "imguiManager.h"
#include <thread>
#include <mutex>
#include <future>

char ImguiManager::m_Buffer[1024];

void ImguiManager::Init()
{

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.DisplaySize.x = SCREEN_WIDTH;
    io.DisplaySize.y = SCREEN_HEIGHT;

    ImGui_ImplWin32_Init(GetWindow());
	ImGui_ImplDX11_Init(Renderer::GetDevice(), Renderer::GetDeviceContext());
}

void ImguiManager::Uninit()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();

    ImGui::DestroyContext();
}

void ImguiManager::Begin()
{
    static Vector2 pos(0.0f, 0.0f);
    static float f;
    pos = Input::GetMousePos();


    static ImVec2 windowPos(1.0f, 1.0f);
    static ImVec2 WindowSize(200.0f, 300.0f);

    //ImGui::SetNextWindowPos(windowPos);
    //ImGui::SetNextWindowSize(WindowSize);
    static bool b = true;

        b = false;
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();

        ImGui::NewFrame();
        ImGui::Begin("hoge", 0, ImGuiWindowFlags_MenuBar);
        ImGui::Text("%f,%f", pos.x, pos.y);
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

    
}


void ImguiManager::End()
{
    ImGui::End();
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
