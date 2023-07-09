#pragma once
#include "gameObject.h"

class Player :public GameObject
{
private:
	int m_Index = -1;

	ID3D11ShaderResourceView* m_TextureNormalMap = NULL;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

};