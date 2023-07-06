#include "main.h"
#include "renderer.h"
#include "model.h"
#include "player.h"
#include "modelManager.h"
#include "material.h"
#include "camera.h"
#include "input.h"
void Player::Init()
{

	//AddComponent<Model>()->Load("asset\\model\\torus.obj");
	//SetComponent<Model>(ModelManager::Road((char*)"asset\\model\\torus.obj"));
	m_Index = ModelManager::Road((char*)"asset\\model\\torus.obj");
	AddComponent<Matelial>()->Init("shader\\unlitTextureVS.cso",
								   "shader\\unlitTexturePS.cso");
	GameObject::Init();
}

void Player::Uninit()
{
	GameObject::Uninit();
}

void Player::Update()
{
	Vector3 vec;
	if (Input::GetKeyPress('W'))
		vec += Vector3().Forward();

	if (Input::GetKeyPress('A'))
		vec += Vector3().Right() * -1.0f;

	if (Input::GetKeyPress('S'))
		vec += Vector3().Forward() * -1.0f;

	if (Input::GetKeyPress('D'))
		vec += Vector3().Right();

	if (Input::GetKeyPress('K'))
		vec.NormalizThis();
	//D3DXVec3Normalize((D3DXVECTOR3*)&vec, (D3DXVECTOR3*)&vec);

	m_Position += vec * 0.5f;


	GameObject::Update();
}

void Player::Draw()
{
	//マトリックス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);
	GameObject::Draw();
	ModelManager::GetModel(m_Index)->Draw();

}
