#pragma once
#include "component.h"

class Sprite:public Component
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	int m_Index = -1;
public:
	void Init(const char*  file);
	void Uninit()override;
	void Update()override;
	void Draw()override;

};