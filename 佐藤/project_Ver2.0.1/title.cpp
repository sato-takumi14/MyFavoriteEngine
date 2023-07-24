#include"main.h"
#include "manager.h"
#include "renderer.h"
#include "title.h"
#include "titleLogo.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include"layer.h"
#include"layerOrder.h"

void Title::Init()
{
	Scene::Init();

	SetLayer("fade");
	
	AddGameObject<TitleLogo>();
	m_Fade = AddGameObject<Fade>("fade");

	//Layer::AddLayer("2D");
	//Layer::AddLayer("2Dsecond");
	//Layer::SetLayer("2D", AddGameObject<TitleLogo>());
	//m_Fade = AddGameObject<Fade>();
	//Layer::SetLayer("2Dsecond", m_Fade);
	//LayerOrder::ChangeLayerName(LayerOrder::GetOrder("2D"), 0);
	//LayerOrder::ChangeLayerName(LayerOrder::GetOrder("2Dsecond"), 1);
}
void Title::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN))
		m_Fade->FadeOut();
	
	if (m_Fade->GetFadeFinish())
		Manager::SetSceneLoad(new Game);
}