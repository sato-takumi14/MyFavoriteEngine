#pragma once
#include <list>
#include <vector>
#include"textureManager.h"
#include "modelManager.h"
#include "prigon2D.h"
#include "player.h"
#include "field.h"
#include "camera.h"
class Scene
{
private:
	std:: list<GameObject*> m_GameObjects;
public:
	void Init()
	{
		AddGameObject<Camera>();
		AddGameObject<Player>();
		AddGameObject<Field>();
		AddGameObject<Polygon2D>();

	}

	void Uninit()
	{
		for (GameObject* gameObject:m_GameObjects)
		{
			gameObject->Uninit();
			delete gameObject;
		}
		
		m_GameObjects.clear();
		TextureManager::Uninit();
		ModelManager::Uninit();

	}
	void Update()
	{
		for (GameObject* gameObject : m_GameObjects)
		{
			gameObject->Update();
		}
		m_GameObjects.remove_if([](GameObject* object) {return object->Destroy(); });
	}

	void Draw()
	{
		for (GameObject* gameObject : m_GameObjects)
		{
			gameObject->Draw();
		}
	}

	template<typename T>
	T* AddGameObject()
	{
		GameObject* gameObject = new T;
		m_GameObjects.push_back(gameObject);
		gameObject->Init();

		return dynamic_cast<T*>(gameObject);
	}

	template<typename T>
	std::vector<T*>GetGameObjects()
	{
		std::vector<T*>objects;
		for (GameObject* object : m_GameObjects)
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}
		return objects;
	}
};