
#include"main.h"
#include "collider.h"
#include"gameObject.h"

void Collider::Init(GameObject* obj, Transform* transform, Vector3 offset, float radius)
{
	m_Object = obj;
	m_Transform = transform;
	m_Offset = offset;
	m_Radius = radius;
}

void Collider::Update()
{
	for (auto& obj : m_Objects) {
		m_Object->OnCollisionStay(obj);
	}
}

void Collider::Uninit()
{
	m_Objects.clear();
}

void Collider::OnCollisionEnter(GameObject* obj)
{

	bool flag = true;

	for (auto& target : m_Objects) {
		if (target == obj) {
			flag = false;
			break;
		}
	}

	if (flag) {
		m_Object->OnCollisionEnter(obj);
		m_Objects.push_back(obj);
	}

}

void Collider::OnCollisionExit(GameObject* obj)
{

	m_Objects.remove_if([obj](GameObject* target) {
		if (obj == target) {
			target->OnCollisionExit(obj);
			return true;
		}
		return false;
		});

}

GameObject* Collider::GetGameObject()
{
	return m_Object;
}

const bool Collider::GetDestroy() const
{
	return m_Object->GetDestroy();
}

Vector3 Collider::GetPosition() const
{
	return m_Transform->GetWorldPosition() + m_Offset;
}
