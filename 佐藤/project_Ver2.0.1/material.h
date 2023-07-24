#pragma once
#include "component.h"
class Material:public Component
{
private:
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXCOLOR m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
public:
	void Init(const char* VS, const char* PS);
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SetColor(D3DXCOLOR Color) { m_Color = Color; }
};