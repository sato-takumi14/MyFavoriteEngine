#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "imguiManager.h"
#include "input.h"
#include "scene.h"


Scene* scene;
void Manager::Init()
{
	Renderer::Init();
	ImguiManager::Init();
	Input::Init();
	scene = new Scene();
	scene->Init();

}

void Manager::Uninit()
{
	scene->Uninit();

	Input::Uninit();
	ImguiManager::Uninit();
	Renderer::Uninit();
}

void Manager::Update()
{
	Input::Update();
	scene->Update();
}

void Manager::Draw()
{
	Renderer::Begin();
	ImguiManager::Begin();

	scene->Draw();

	ImguiManager::End();
	Renderer::End();
}
