#pragma once
#include "scene.h"
#include <mutex>

#define PATTERN_X (1.0f / 3.0f)
#define PATTERN_Y (1.0f / 4.0f)

class Load :public Scene
{
private:
	ID3D11Buffer* m_VertexBuffer{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	int m_Index = -1;

	bool m_Loaded = false;
	std::mutex m_LoadedMutex{};
	Scene* m_NextScene = nullptr;

	int m_Count = 0;
public:

	Load() {}
	Load(Scene* next_scene): m_NextScene(next_scene){}
	void Init()override;
	void Update()override;
	void Uninit()override;
	void Draw()override;

	void AsyncLoad()
	{
		// ここで m_NextScene へのアクセスをロックする
		{
			std::lock_guard<std::mutex> lock(m_LoadedMutex);
			m_NextScene->Init(); // m_NextScene は nullptr の場合にアクセスしないように修正
			//m_NextScene->Draw();
		}

		SetLockFlag(true);
	}

	void SetLockFlag(bool Load)
	{
		m_Loaded = true;
	}

	bool GetLockFlag()
	{
		return m_Loaded;
	}
};