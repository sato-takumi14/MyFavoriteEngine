#pragma once
#include "gameObject.h"

class Polygon2D : public GameObject
{
private:

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};