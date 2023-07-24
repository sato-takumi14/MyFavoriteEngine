#pragma once
#include"main.h"
#include"component.h"
#include"transform.h"
#include"debug.h"
#include <list>

class GameObject
{
protected:
	bool m_Destroy = false;
	std::list<Component*> m_Componets;
	Transform* m_Transform;
	int m_LayerNum;

	string m_Tag{};
	float m_Radius{};/*“–‚½‚è”»’è‚·‚é‘å‚«‚³*/

public:
	void SetLayerNum(int layer) { m_LayerNum = layer; }
	void SetDestroy() { m_Destroy = true; }
	int GetLayerNum() { return m_LayerNum; }
	const float GetRadius()const { return m_Radius; }//š
	const bool GetDestroy()const { return m_Destroy; }//š
	bool Destroy()
	{
		if (m_Destroy)
		{

#if _DEBUG
			Debug::DestroyAlert(m_Tag);

#endif // _DEBUG

			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}

	const string GetTag()const { return m_Tag; }

	Transform* GetTransform() { return m_Transform; }

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

	/*“–‚½‚è”»’è‚Ì‚ÉŒÄ‚Ño‚·ŠÖ”*/
	virtual void OnCollisionEnter(GameObject* obj) {}
	virtual void OnCollisionExit(GameObject* obj) {}
	virtual void OnCollisionStay(GameObject* obj) {}

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