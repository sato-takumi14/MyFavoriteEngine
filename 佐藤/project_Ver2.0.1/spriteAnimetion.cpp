#include "main.h"
#include "renderer.h"
#include "textureManager.h"
#include "spriteAnimation.h"



void SpriteAnimation::Init(float x, float y, float width, float height, int divide_x, int divide_y,int anim_speed,int loop, const  char* file)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Scale.x = width;
	m_Scale.y = height;
	m_Divide.x = divide_x;
	m_Divide.y = divide_y;
	m_AnimSpeed = anim_speed;
	m_Loop = loop;

	m_NumTexture = divide_x * divide_y;
	m_Pattern.x = (1.0f / m_Divide.x);
	m_Pattern.y = (1.0f / m_Divide.y);
	

	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(x, y, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(x + width, y, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(m_Pattern.x, 0.0f);

	vertex[2].Position = D3DXVECTOR3(x, y + height, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, m_Pattern.y);

	vertex[3].Position = D3DXVECTOR3(x + width, y + height, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(m_Pattern.x, m_Pattern.y);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	m_Index = TextureManager::Load(file);
}

void SpriteAnimation::Uninit()
{
	m_VertexBuffer->Release();
	//m_Texture->Release();

}

void SpriteAnimation::Update()
{
	static int count = 0;
	count++;
	if (m_Loop == 0)
	{
		if (count >= m_AnimSpeed)
		{
			if (m_Count >= m_NumTexture)
				m_Count = 0;

			m_Count++;
			count = 0;
		}
	}
	else
	{
		static int index = 0;

		if (count >= m_AnimSpeed)
		{
			if (m_Count >= m_NumTexture)
			{
				index++;
				if (index == m_Loop)
				{
					m_AnimFinish = true;
					return;
				}
				m_Count = 0;
			}

			m_Count++;
			count = 0;
		}
	}
}

void SpriteAnimation::Draw()
{
	//テクスチャ座標書き換え
	float u = m_Count % (int)m_Divide.x * m_Pattern.x;
	float v = m_Count / (int)m_Divide.x * m_Pattern.y;

	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(m_Position.x, m_Position.y, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(u, v);

	vertex[1].Position = D3DXVECTOR3(m_Position.x + m_Scale.x, m_Position.y, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(u + m_Pattern.x, v);

	vertex[2].Position = D3DXVECTOR3(m_Position.x, m_Position.y + m_Scale.y, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(u, v + m_Pattern.y);

	vertex[3].Position = D3DXVECTOR3(m_Position.x + m_Scale.x, m_Position.y + m_Scale.y, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(u + m_Pattern.x, v + m_Pattern.y);

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = m_Color;
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, TextureManager::GetTexture(m_Index));

	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);
}

