#include "main.h"
#include "renderer.h"
#include "field.h"
#include "plane.h"
#include "material.h"

void Field::Init()
{
	AddComponent<Material>()->Init("shader\\unlitTextureVS.cso", "shader\\unlitTexturePS.cso");
	AddComponent<Plane>()->Init(0.0f, 0.0f, 0.0f, 15.0f, 15.0f);
	GameObject::Init();

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
	Vector3 posVec = m_Transform->GetWorldPosition();
	Vector3 rotVec = m_Transform->GetWorldRotation();
	Vector3 sclVec = m_Transform->GetWorldScale();

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, sclVec.x, sclVec.y, sclVec.z);
	D3DXMatrixRotationYawPitchRoll(&rot, rotVec.y, rotVec.x, rotVec.z);
	D3DXMatrixTranslation(&trans, posVec.x, posVec.y, posVec.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	GameObject::Draw();
}

