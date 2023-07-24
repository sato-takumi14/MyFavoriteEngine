#include"main.h"
#include "manager.h"
#include"layer.h"
#include"layerOrder.h"
#include "renderer.h"
#include "result.h"
#include "resultLogo.h"
#include "title.h"
#include "input.h"
#include "fade.h"



void Result::Init()
{
	Scene::Init();

	SetLayer("2D");
	SetLayer("fade");
	AddGameObject<ResultLogo>("2D");
	m_Fade = AddGameObject<Fade>("fade");
}
void Result::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN))
		m_Fade->FadeOut();

	if(m_Fade->GetFadeFinish())
		Manager::SetScene<Title>();
	
}