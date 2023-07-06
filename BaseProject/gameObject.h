#pragma once
#include"component.h"
#include <list>
class GameObject
{
protected:
	bool m_Destroy = false;
	Vector3 m_Position = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_Rotation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_Scale = Vector3(1.0f, 1.0f, 1.0f);
	std::list<Component*> m_Componets;

public:
	void SetPosition(Vector3 pos) { m_Position = pos; }
	Vector3 GetPosition() { return m_Position; }
	void SetDestroy() { m_Destroy = true; }

	Vector3 GetForward()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		Vector3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}
	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}


	Vector3 GetRight()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		Vector3 right;
		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;

		return right;
	}
	virtual void Init()
	{
	}
	virtual void Uninit()
	{
		for (Component* component : m_Componets)
		{
			component->Uninit();
		}
	}
	virtual void Update()
	{
		for (Component* component : m_Componets)
		{
			component->Update();
		}
	}
	virtual void Draw()
	{
		for (Component* component : m_Componets)
		{
			component->Draw();
		}
	}

	template<typename T>
	T* AddComponent()
	{
		Component* component = new T;
		m_Componets.push_back(component);
		component->Init();

		return dynamic_cast<T*>(component);
	}

	template<typename T>
	T* SetComponent(T* com)
	{
		Component* component = com;
		m_Componets.push_back(component);

		return dynamic_cast<T*>(component);

	}

	template<typename T>
	T* GetComponent()
	{
		for (Component* component : m_Componets)
		{
			if (typeid(*component) == typeid(T))//Œ¨‚ğ’²‚×‚é(RTTI“®“IŒ^î•ñ)
			{
				return (T*)component;
			}
		}
		return nullptr;

	}
};