#pragma once
#include "gameObject.h"

class Camera:public GameObject
{
private:

	Vector3 m_Target{};
	D3DXMATRIX m_ViewMatrix{};

public:
	void Init();
	void Update();
	void Draw();
};
