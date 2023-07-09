#pragma once
#include "gameObject.h"

class FogField:public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11Buffer* m_IndexBuffer{};

	int	m_numVertex{};
	int	m_numIndex{};

	ID3D11ShaderResourceView* m_Texture{};
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};