#pragma once
#include "gameObject.h"

class Fade :public GameObject
{
private:
	class Material* m_Material{};

	float m_Alpha = 1.0f;
	bool  m_FadeOut = false;
	bool  m_FadeFinish = false;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void FadeOut() { m_FadeOut = true; }
	bool GetFadeFinish() { return m_FadeFinish; }
};