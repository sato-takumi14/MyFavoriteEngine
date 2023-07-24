#include"main.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "result.h"
#include "textureManager.h"
#include "input.h"
#include "prigon2D.h"
#include "player.h"
#include "field.h"
#include "camera.h"
#include "fogField.h"
#include "fieldNM.h"
#include "fade.h"
#include"layer.h"
#include"layerOrder.h"
#include"enemy.h"

void Game::Init()
{
	Scene::Init();

	SetLayer("camera");
	SetLayer("3D");
	SetLayer("2D");
	SetLayer("effect");
	SetLayer("bg");
	SetLayer("fade");
	AddGameObject<Camera>("camera");
	AddGameObject<Field>("3D");
	AddGameObject<Player>("3D");
	AddGameObject<Enemy>("3D");
	AddGameObject<Polygon2D>("2D");
	m_Fade = AddGameObject<Fade>("fade");

}

void Game::Uninit()
{
	Scene::Uninit();
}
void Game::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN))
		m_Fade->FadeOut();

	if(m_Fade->GetFadeFinish())
		Manager::SetScene<Result>();
}