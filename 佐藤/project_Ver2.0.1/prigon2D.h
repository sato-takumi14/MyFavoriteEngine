#pragma once
#include "gameObject.h"

class Polygon2D : public GameObject
{
private:
	//�q�b�g�|�C���g�֘A
	int m_hp;       //���݃q�b�g�|�C���g
	int m_hpMax;    //�ő�q�b�g�|�C���g
	int m_hpOld;    //�O��q�b�g�|�C���g

	int m_Count;

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};