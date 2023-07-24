//�O���錾�̓|�C���^�Ŏg�����̂�
//�p���ɂ͎g�p�s��

#include "scene.h"
#include "post.h"

class Manager
{
private:
	//Maneger�̓C���X�^���X���Ȃ��̂ŐÓI�ɍ��
	static Scene* m_Scene;
	static Scene* m_NextScene;
	static Scene* m_NextSceneLoad;

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static Scene* GetScene(void) { return m_Scene; }

	template<typename T>
	static void SetScene()
	{
		m_NextScene = new T();
	}

	static void SetScene(Scene* next_scene)
	{
		m_NextSceneLoad= next_scene;
	}

	static void SetSceneLoad(Scene* next_scene);

};