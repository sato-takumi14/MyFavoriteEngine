#pragma once
#include "gameObject.h"

class Polygon2D : public GameObject
{
private:
	//ヒットポイント関連
	int m_hp;       //現在ヒットポイント
	int m_hpMax;    //最大ヒットポイント
	int m_hpOld;    //前回ヒットポイント

	int m_Count;

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};