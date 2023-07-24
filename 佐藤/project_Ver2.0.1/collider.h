#pragma once

/******************************************************************************************************
*
*		[collider.h]
*																	����ҁF������
*																	�쐬���F07/23
*
*******************************************************************************************************
* Collider : �����蔻�������Q�[���I�u�W�F�N�g�Ɋ��蓖�Ă�
* �I�u�W�F�N�g�̓����蔻��p�̊֐��������I�ɌĂяo��
*******************************************************************************************************/

#include<list>

#include"component.h"

using namespace std;

class Collider : public Component
{
protected:

	class GameObject* m_Object{};
	class Transform* m_Transform{};
	float m_Radius{};
	Vector3 m_Offset{};
	list<GameObject*> m_Objects;

public:

	virtual void Init(GameObject* obj, Transform* transform, Vector3 offset, float radius);
	void Update()override;
	void Uninit()override;

	void OnCollisionEnter(GameObject* obj);
	void OnCollisionExit(GameObject* obj);

	void SetRadius(float radius) { m_Radius = radius; }

	GameObject* GetGameObject();
	const bool GetDestroy()const;
	Vector3 GetPosition()const;
	const float GetRadius()const { return m_Radius; }

};