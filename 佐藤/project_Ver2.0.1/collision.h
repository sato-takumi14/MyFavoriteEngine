#pragma once

/******************************************************************************************************
* 
*		[collision.h]
*																	制作者：佐藤匠
*																	作成日：07/23
* 
*******************************************************************************************************
* Collision : 当たり判定をするクラス
* コライダーゲームオブジェクトに加えれば自動的にセットするようにしてある
*******************************************************************************************************/

#include<list>
#include<algorithm>

#include"collider.h"

using namespace std;

class Collision
{
private:

	static list<Collider*> m_Circle;		//CircleCollider
	static list<Collider*> m_Box;			//BoxCollider

	static bool HitCheckCircle(Collider* hit, Collider* washit);		//円の当たり判定
	static bool HitCheckBox(Collider* hit, Collider* washit);			//四角の当たり判定

	static void OnCollisionEnter();			//当たった初めの時
	static void OnCollisionExit();			//当たらなくなったら

public:

	static void Update();
	static void Uninit();

	static void SetCircleCollider(Collider* collider);
	static void SetBoxCollider(Collider* collider);

};