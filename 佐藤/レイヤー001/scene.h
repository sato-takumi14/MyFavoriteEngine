#pragma once
#include <list>
#include <vector>
#include"textureManager.h"
#include "modelManager.h"
#include "prigon2D.h"
#include "player.h"
#include "field.h"
#include "camera.h"
#include"layer.h"
#include"layerOrder.h"

class Scene
{
private:

	std:: list<GameObject*> m_GameObjects;
	//Layer* m_Layer{};

public:
	void Init()
	{
		//m_Layer = new Layer();

		Layer::AddLayer("effect");
		Layer::AddLayer("bg");
		Layer::AddLayer("3D");
		Layer::AddLayer("2D");
		Layer::AddLayer("camera");

		Layer::SetLayer("3D", AddGameObject<Player>());
		Layer::SetLayer("2D", AddGameObject<Polygon2D>());
		Layer::SetLayer("camera", AddGameObject<Camera>());
		Layer::SetLayer("3D", AddGameObject<Field>());

		/*ç°åªç›ëSïîÇ±ÇÃä÷êîÇåƒÇŒÇ»Ç¢Ç∆Ç±ÇÃèáî‘Ç…Ç»ÇÁÇ»Ç¢*/
		LayerOrder::ChangeLayerName(LayerOrder::GetOrder("camera"), 0);
		LayerOrder::ChangeLayerName(LayerOrder::GetOrder("3D"), 1);
		LayerOrder::ChangeLayerName(LayerOrder::GetOrder("2D"), 2);
		LayerOrder::ChangeLayerName(LayerOrder::GetOrder("effect"), 3);
		LayerOrder::ChangeLayerName(LayerOrder::GetOrder("bg"), 4);

		/*AddGameObject<Camera>();
		AddGameObject<Player>();
		AddGameObject<Field>();
		AddGameObject<Polygon2D>();*/

	}

	void Uninit()
	{
		for (GameObject* gameObject:m_GameObjects)
		{
			gameObject->Uninit();
			delete gameObject;
		}
		
		//m_Layer->Uninit();
		Layer::Uninit();

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
		/*for (GameObject* gameObject : m_GameObjects)
		{
			gameObject->Draw();
		}*/

		//m_Layer->Draw();
		Layer::Draw();
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