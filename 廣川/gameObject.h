#pragma once
#include"component.h"
#include"transform.h"
#include <list>
class GameObject
{
protected:
	bool m_Destroy = false;
	std::list<Component*> m_Componets;
	Transform* m_Transform;

public:
	void SetDestroy() { m_Destroy = true; }

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

	virtual void Init()
	{
		m_Transform = AddComponent<Transform>();
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