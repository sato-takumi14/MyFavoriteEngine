#include "main.h"
#include "renderer.h"
#include "titleLogo.h"
#include "sprite.h"
#include "material.h"

void TitleLogo::Init()
{
	AddComponent<Material>()->Init("shader\\unlitTextureVS.cso", "shader\\unlitTexturePS.cso");

	m_sprite = AddComponent<Sprite>();
	m_sprite->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, (char*)"asset\\texture\\title.png");
}

void TitleLogo::Uninit()
{
	GameObject::Uninit();
}
void TitleLogo::Update()
{
	GameObject::Update();
}

void TitleLogo::Draw()
{
	//�}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();
}