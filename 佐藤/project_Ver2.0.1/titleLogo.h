#pragma once
#include "gameObject.h"

class TitleLogo :public GameObject
{
private:
	class Sprite* m_sprite{};
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};