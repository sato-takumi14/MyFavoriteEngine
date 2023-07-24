#pragma once

/******************************************************************************************************
*
*		[boxcollider.h]
*																	����ҁF������
*																	�쐬���F07/23
*
*******************************************************************************************************
* CircleCollider :	�l�p�͈̔͂𓖂��蔻��������ۂ�
�Q�[���I�u�W�F�N�g�̓����蔻����Ăяo���悤�ɂ��Ă���
*******************************************************************************************************/

#include"collider.h"
#include"vector.h"
#include"collision.h"

class BoxCollider : public Collider
{
private:



public:

	void Init(GameObject* obj, Transform* transform, Vector3 offset, float radius)override {
		Collider::Init(obj, transform, offset, radius);
		Collision::SetBoxCollider(this);
	}

};