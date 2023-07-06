#include "main.h"
#include "renderer.h"
#include "prigon2D.h"
#include "sprite.h"
#include "material.h"

void Polygon2D::Init()
{
	AddComponent<Matelial>()->Init("shader\\unlitTextureVS.cso",
								   "shader\\unlitTexturePS.cso");
	AddComponent<Sprite>()->Init((char*)"asset/texture/test.jpg");
}

void Polygon2D::Uninit()
{
	GameObject::Uninit();
}

void Polygon2D::Update()
{
	GameObject::Update();
}

void Polygon2D::Draw()
{
	//マトリックス設定
	Renderer::SetWorldViewProjection2D();

	GameObject::Draw();

}
