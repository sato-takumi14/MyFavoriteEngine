#pragma once
#include "gameObject.h"
#include "renderer.h"
#include <list>
#include <typeinfo>
#include <vector>
#include <map>

#include"textureManager.h"
#include "modelManager.h"
#include"layer.h"
#include"layerOrder.h"
#include "post.h"
#include"collision.h"

using namespace std;

class Scene
{
private:
	list<GameObject*> m_GameObjects;
	map<string, int> m_DrawOder;

	int m_LayerNum = 0;
	Post m_Post{};
public:
	void SetLayer(string name) 
	{
		m_DrawOder[name] = m_LayerNum++;
	}
	void SetLayer(string name,int num) 
	{
		if (num == m_LayerNum)
		{
			m_DrawOder[name] = m_LayerNum++;
		}
		else if (num < m_LayerNum)
		{
			for (int i = m_LayerNum - 1; i > num; i--)
			{
				string key;
				for (const auto& pair : m_DrawOder) {
					if (pair.second == i) {
						key = pair.first;
						break; // 見つかったらループを抜ける
					}
				}
				m_DrawOder[key] = i + 1;
			}
			m_LayerNum++;
			m_DrawOder[name] = num;
		}
		else
		{
			assert("要素数はそんなにありません");
		}
	}

	virtual void Init()
	{
		m_DrawOder["None"] = m_LayerNum++;
		m_Post.Init();
	}

	virtual void Uninit()
	{
		for (GameObject* gameObject:m_GameObjects)
		{
			gameObject->Uninit();
			delete gameObject;
		}

		Debug::Uninit();//★
		Collision::Uninit();//★
		m_Post.Uninit();
		Layer::Uninit();
		m_GameObjects.clear();
		TextureManager::Uninit();
		ModelManager::Uninit();
	}

	virtual void Update()
	{
		for (GameObject* gameObject : m_GameObjects)
		{
			gameObject->Update();
		}

		Collision::Update();//★
		Debug::Update();//★

		m_GameObjects.remove_if([](GameObject* object) {return object->Destroy(); });

		m_Post.Update();
	}

	virtual void Draw()
	{
		Renderer::BeginPP();
		for (int i = 0; i < m_LayerNum; i++)
		{
			for (GameObject* gameObject : m_GameObjects)
			{
				if (m_DrawOder["fade"] == i)
				{
					Renderer::Begin();
					m_Post.Draw();
				}
				if(i == gameObject->GetLayerNum())
					gameObject->Draw();
			}
		}

		//Layer::Draw();

	}

	//template<typename T>
	//T* AddGameObject()
	//{
	//	GameObject* gameObject = new T;
	//	m_GameObjects.push_back(gameObject);
	//	gameObject->Init();
	//	return dynamic_cast<T*>(gameObject);
	//}

	template<typename T>
	T* AddGameObject(string name = "None")
	{
		GameObject* gameObject = new T;
		m_GameObjects.push_back(gameObject);
		gameObject->Init();

		gameObject->SetLayerNum(m_DrawOder[name]);
	
		return dynamic_cast<T*>(gameObject);
	}
	//template<typename T>//テンプレート関数
	//T* GetGameObject()
	//{
	//	for (GameObject* object : m_GameObject)
	//	{
	//		メモリをくうのであまり使わないほうがいい
	//		if (typeid(*object) == typeid(T))//型を調べる(RTTI動的型情報)
	//		{
	//			return(T*)object;
	//		}
	//	}
	//	return nullptr;
	//}

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