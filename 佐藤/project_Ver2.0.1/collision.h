#pragma once

/******************************************************************************************************
* 
*		[collision.h]
*																	����ҁF������
*																	�쐬���F07/23
* 
*******************************************************************************************************
* Collision : �����蔻�������N���X
* �R���C�_�[�Q�[���I�u�W�F�N�g�ɉ�����Ύ����I�ɃZ�b�g����悤�ɂ��Ă���
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

	static bool HitCheckCircle(Collider* hit, Collider* washit);		//�~�̓����蔻��
	static bool HitCheckBox(Collider* hit, Collider* washit);			//�l�p�̓����蔻��

	static void OnCollisionEnter();			//�����������߂̎�
	static void OnCollisionExit();			//������Ȃ��Ȃ�����

public:

	static void Update();
	static void Uninit();

	static void SetCircleCollider(Collider* collider);
	static void SetBoxCollider(Collider* collider);

};