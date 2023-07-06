#include "main.h"
#include "renderer.h"
#include "field.h"
#include "plane.h"
#include "material.h"

void Field::Init()
{
	AddComponent<Matelial>()->Init("shader\\unlitTextureVS.cso", "shader\\unlitTexturePS.cso");
	AddComponent<Plane>()->Init(0.0f, 0.0f, 0.0f, 15.0f, 15.0f);
}

void Field::Uninit()
{

	GameObject::Uninit();
}

void Field::Update()
{
	GameObject::Update();

}

void Field::Draw()
{

	//マトリックス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	GameObject::Draw();

}

