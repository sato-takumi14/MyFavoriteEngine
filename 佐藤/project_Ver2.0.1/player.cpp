#include "main.h"
#include "renderer.h"
#include "player.h"
#include "modelManager.h"
#include "material.h"
#include "camera.h"
#include "input.h"
#include"circleCollider.h"

void Player::Init()
{

	//AddComponent<Model>()->Load("asset\\model\\torus.obj");
	//SetComponent<Model>(ModelManager::Road((char*)"asset\\model\\torus.obj"));
    m_Index = ModelManager::Load((char*)"asset\\model\\torus.obj");
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

	AddComponent<CircleCollider>()->Init(this, m_Transform, Vector3(0.0f, 0.0f, 0.0f), 1.5f);

	m_Tag = "Player";

}

void Player::Uninit()
{
	m_TextureNormalMap->Release();
	GameObject::Uninit();
}

void Player::Update()
{
	//Debug::MothodName(FUNCTIONNAME, m_Tag);

	Vector3 vec;
	if (Input::GetKeyPress('W'))
		vec += Vector3().Forward();

	if (Input::GetKeyPress('A'))
		vec += Vector3().Right() * -1.0f;

	if (Input::GetKeyPress('S'))
		vec += Vector3().Forward() * -1.0f;

	if (Input::GetKeyPress('D'))
		vec += Vector3().Right();

	if (Input::GetKeyPress('R'))
		m_Transform->Rotate(Vector3(-0.1f, 0.0f, 0.0f));
	if (Input::GetKeyPress('F'))
		m_Transform->Rotate(Vector3(0.1f, 0.0f, 0.0f));

	if (Input::GetKeyPress('Q'))
		m_Transform->Rotate(Vector3(0.0f, -0.1f, 0.0f));

	if (Input::GetKeyPress('E'))
		m_Transform->Rotate(Vector3(0.0f, 0.1f, 0.0f));

	if (Input::GetKeyPress('K'))
		vec.NormalizThis();
	//D3DXVec3Normalize((D3DXVECTOR3*)&vec, (D3DXVECTOR3*)&vec);

	m_Transform->Translate(vec * 0.5f);

	GameObject::Update();
}

void Player::Draw()
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
	ModelManager::GetModel(m_Index)->Draw();

}

void Player::OnCollisionEnter(GameObject* obj)
{
	cdbg << "当たりはじめ" << endl;
}

void Player::OnCollisionExit(GameObject* obj)
{
	cdbg << "離れた" << endl;
}

void Player::OnCollisionStay(GameObject* obj)
{
	cdbg << "当たり続けている" << endl;
}
