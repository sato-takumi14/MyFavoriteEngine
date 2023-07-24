#pragma once
#include "gameObject.h"

class ResultLogo :public GameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};