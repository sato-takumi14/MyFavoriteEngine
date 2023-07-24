#pragma once

/******************************************************************************************************
*
*		[boxcollider.h]
*																	制作者：佐藤匠
*																	作成日：07/23
*
*******************************************************************************************************
* CircleCollider :	四角の範囲を当たり判定をした際に
ゲームオブジェクトの当たり判定を呼び出すようにしてある
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