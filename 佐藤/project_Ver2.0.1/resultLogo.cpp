#include "main.h"
#include "renderer.h"
#include "resultLogo.h"
#include "sprite.h"
#include "material.h"

void ResultLogo::Init()
{
	AddComponent<Material>()->Init("shader\\unlitTextureVS.cso", "shader\\unlitTexturePS.cso");

	AddComponent<Sprite>()->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, (char*)"asset\\texture\\result.png");
}

void ResultLogo::Uninit()
{
	GameObject::Uninit();
}
void ResultLogo::Update()
{
	GameObject::Update();
}

void ResultLogo::Draw()
{
	//�}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();
}