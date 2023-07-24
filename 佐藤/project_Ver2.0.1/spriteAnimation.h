#pragma once
#include "component.h"

class SpriteAnimation :public Component
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	int m_Index = -1;

	D3DXCOLOR m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Vector2 m_Position{};
	Vector2 m_Scale{};
	Vector2 m_Divide{};
	Vector2 m_Pattern{};

	int m_Count{};
	int m_AnimSpeed{};
	int m_NumTexture{};
	int m_Loop{};
	bool m_AnimFinish = false;

public:
	void Init(float x, float y, float width, float height,int divide_x,int divide_y,int anim_speed, int loop ,const  char* file);
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SetColor(D3DXCOLOR color) { m_Color = color; }
	void SetPositionX(float x) { m_Position.x = x; }
	void SetPositionY(float y) { m_Position.y = y; }
	void SetPosition(Vector2 positon) { m_Position = positon; }
	void SetScaleX(float width) { m_Scale.x = width; }
	void SetScaleY(float height) { m_Scale.y = height; }
	void SetScale(Vector2 scale) { m_Scale = scale; }
	void SetAnimSpeed(int speed) { m_AnimSpeed = speed;}
	void SetAnimNumTexture(int num) { m_NumTexture = num; }
};