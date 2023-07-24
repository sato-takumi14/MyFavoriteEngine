#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "imguiManager.h"
#include "input.h"
#include "scene.h"
#include "post.h"
#include "title.h"
#include "game.h"
#include "load.h"

Scene* Manager::m_Scene{};//静的メンバ変数は再宣言が必要
Scene* Manager::m_NextScene{};
Scene* Manager::m_NextSceneLoad{};

void Manager::Init()
{
	Renderer::Init();
	ImguiManager::Init();
	Input::Init();

	SetScene<Title>();

}

void Manager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;


	Input::Uninit();
	ImguiManager::Uninit();
	Renderer::Uninit();
}

void Manager::Update()
{
	Input::Update();

	if (m_NextScene)
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}

		m_Scene = m_NextScene;
		m_Scene->Init();

		m_NextScene = nullptr;
	}

	if (m_NextSceneLoad)
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}

		
		m_Scene = m_NextSceneLoad;
		

		m_NextSceneLoad = nullptr;
	}

	m_Scene->Update();

}

void Manager::Draw()
{
	ImguiManager::Begin();

    m_Scene->Draw();

	ImguiManager::End();
	Renderer::End();

}

void Manager::SetSceneLoad(Scene* next_scene)
{
	m_NextScene = new Load(next_scene);
}