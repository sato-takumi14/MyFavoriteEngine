
#include "main.h"
#include"renderer.h"
#include "enemy.h"
#include "modelManager.h"
#include "material.h"
#include"circleCollider.h"

void Enemy::Init()
{
	m_ModelID = ModelManager::Load((char*)"asset\\model\\torus.obj");
	/// m_Index = ModelManager::Road((char*)"asset\\model\\doragon12.obj");

	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/fieldNormal.png",
		NULL,
		NULL,
		&m_TextureNormalMap,
		NULL);
	assert(m_TextureNormalMap);

	AddComponent<Material>()->Init("shader\\normalMappingVS.cso",
		"shader\\normalMappingPS.cso");

	GameObject::Init();

	m_Transform->SetWorldPosition(Vector3(0.0f, 0.0f, 5.0f));

	AddComponent<CircleCollider>()->Init(this, m_Transform, Vector3(0.0f, 0.0f, 0.0f), 1.5f);

	m_Tag = "Enemy";

}

void Enemy::Update()
{

	/*float rot = m_Transform->GetWorldPosition().y;

	Debug::Adjustment(&rot, FUNCTIONNAME, m_Tag, TO_STRING(m_Transform->GetWorldPosition().y));*/

	//m_Transform->Rotate(Vector3(0.0f, rot, 0.0f));

}

void Enemy::Draw()
{
	//マトリックス設定
	Vector3 posVec = m_Transform->GetWorldPosition();
	Vector3 rotVec = m_Transform->GetWorldRotation();
	Vector3 sclVec = m_Transform->GetWorldScale();

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, sclVec.x, sclVec.y, sclVec.z);
	D3DXMatrixRotationYawPitchRoll(&rot, rotVec.y, rotVec.x, rotVec.z);
	D3DXMatrixTranslation(&trans, posVec.x, posVec.y, posVec.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &m_TextureNormalMap);

	GameObject::Draw();
	ModelManager::GetModel(m_ModelID)->Draw();
}

void Enemy::Uninit()
{
	if (m_TextureNormalMap) {
		m_TextureNormalMap->Release();
	}
}
