#pragma once
#include "component.h"
class Matelial:public Component
{
private:
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};
public:
	void Init(const char* VS, const char* PS);
	void Uninit()override;
	void Update()override;
	void Draw()override;
};