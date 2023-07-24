#include "main.h"
#include "renderer.h"
#include "prigon2D.h"
#include "sprite.h"
#include "material.h"

void Polygon2D::Init()
{
	m_hp = 600;
	m_hpMax = 1000;
	m_hpOld = 800;

	AddComponent<Material>()->Init("shader\\hitPointVS.cso",
								   "shader\\hitPointPS.cso");
	AddComponent<Sprite>()->Init(0.0f, 0.0f, 200.0f, 200.0f, (char*)"asset\\texture\\test.jpg");
}

void Polygon2D::Uninit()
{
	GameObject::Uninit();
}

void Polygon2D::Update()
{
	m_Count++;
	if (m_Count > 60)
	{
		m_hpOld = m_hp;
		m_Count = 0;
	}
	m_hp--;
	if (m_hp < 0)
	{
		m_hp = 1000;
	}
	GameObject::Update();
}

void Polygon2D::Draw()
{
	//�}�g���b�N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	PARAMETER param;
	param.hitpoint.x = m_hp;
	param.hitpoint.y = m_hpMax;
	param.hitpoint.z = m_hpOld;

	param.baseColor = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);//��
	if (m_hp < 600)
		param.baseColor = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);//���F
	if (m_hp < 200)
		param.baseColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//��
	param.lostColor = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);//�D�F
	param.diffColor = D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f);//������
	Renderer::SetParameter(param);

	GameObject::Draw();
}
