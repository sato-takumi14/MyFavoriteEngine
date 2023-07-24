#pragma once
#include "gameObject.h"

class Camera:public GameObject
{
private:

	Vector3	    m_Target;
	D3DXVECTOR4 m_Param;
	D3DXCOLOR   m_FogColor;
	D3DXCOLOR   m_GroundFogColor;
	D3DXMATRIX m_ViewMatrix{};

public:
	void Init();
	void Update();
	void Draw();
};
