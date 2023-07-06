#include"main.h"
#include"renderer.h"
#include "material.h"

void Matelial::Init(const char* VS, const char* PS)
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,VS);

	Renderer::CreatePixelShader(&m_PixelShader, PS);
}

void Matelial::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Matelial::Update()
{

}

void Matelial::Draw()
{
	//���̓��C�A�E�g
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);
}
