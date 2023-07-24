#include"main.h"
#include"renderer.h"
#include "material.h"

void Material::Init(const char* VS, const char* PS)
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,VS);

	Renderer::CreatePixelShader(&m_PixelShader, PS);
}

void Material::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Material::Update()
{

}

void Material::Draw()
{
	//���̓��C�A�E�g
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = m_Color;
	material.TextureEnable = true;
	Renderer::SetMaterial(material);
}
