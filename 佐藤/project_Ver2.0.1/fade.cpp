#include "main.h"
#include "renderer.h"
#include "fade.h"
#include "sprite.h"
#include "material.h"
#include "input.h"
#include "imgui_impl_dx11.h"

void Fade::Init()
{

	m_Material = AddComponent<Material>();
	m_Material->Init("shader\\unlitTextureMaterialVS.cso", "shader\\unlitTexturePS.cso");
	AddComponent<Sprite>()->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, "asset\\texture\\fade.png");
}

void Fade::Uninit()
{
	GameObject::Uninit();
}
void Fade::Update()
{
	GameObject::Update();

	if (!m_FadeOut)
	{
		m_Alpha -= 0.03f;
		if (m_Alpha < 0.0f)
			m_Alpha = 0.0f;
	}
	else
	{
		m_Alpha += 0.03f;
		if (m_Alpha > 1.0f)
		{
			m_Alpha = 1.0f;
			m_FadeFinish = true;
		}
	}

	//if (Input::GetKeyPress('W'))
	//{
	//	m_Alpha -= 0.01f;

	//}

	//if (Input::GetKeyPress('S'))
	//{
	//	m_Alpha += 0.01f;

	//}
	m_Material->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Alpha));
}

void Fade::Draw()
{

	ImGui::SliderFloat("alfa", &m_Alpha, 0.0f, 1.0f);

	//マトリクス設定	

	Renderer::SetWorldViewProjection2D();

	////基底クラスのメソッド呼び出し

	GameObject::Draw();
}