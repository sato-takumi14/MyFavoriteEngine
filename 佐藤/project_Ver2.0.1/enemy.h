#pragma once

#include"gameObject.h"

class Enemy : public GameObject
{
private:

	ID3D11ShaderResourceView* m_TextureNormalMap = NULL;

	int m_ModelID = -1;

public:

	void Init()override;
	void Update()override;
	void Draw()override;
	void Uninit()override;

};