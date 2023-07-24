#pragma once

#include<list>
#include<unordered_map>
#include<algorithm>
#include<string>

#include"gameObject.h"

using namespace std;

/****************************************************************************************
*
*		����ҁF������
*		�쐬���F07/11
*		�N���X���FLayerName
*
*****************************************************************************************
* ���C���[�����ƂɊi�[����N���X
*****************************************************************************************/

class LayerName
{
private:

	string m_Name{};						//���C���[��
	list<GameObject*> m_GameObjects;		//�Q�[���I�u�W�F�N�g���i�[

public:

	LayerName() {}

	//���C���[�����Z�b�g����R���X�g���N�^
	LayerName(string name) : m_Name(name) {}

	//�Q�[���I�u�W�F�N�g�Z�b�g
	void AddGameObject(GameObject* obj) { m_GameObjects.push_back(obj); }

	//���C���[���擾
	string GetLayerName() { return m_Name; }

	//����������
	void Init() {
		for (auto& obj : m_GameObjects) {
			obj->Init();
		}
	}

	//�X�V����
	void Update() {}

	//�`�揈��
	void Draw() {
		for (auto& obj : m_GameObjects) {
			obj->Draw();
		}
	}

	//�I������
	void Uninit() {
		m_GameObjects.clear();
	}

};

/****************************************************************************************
*
*		����ҁF������
*		�쐬���F07/11
*		�N���X���FLayer
*
*****************************************************************************************
* �`�揇�Ԃ��Ǘ�����N���X
*****************************************************************************************/

class Layer
{
private:

	static unordered_map<string, LayerName*> m_Layer;	//�e���C���[
	static int m_Index;									//���݂̃��C���[�ԍ�

public:

	//���C���[�ɃQ�[���I�u�W�F�N�g���Z�b�g
	static void SetLayer(string name, GameObject* obj);

	//�V�K���C���[�ǉ�
	static void AddLayer(string name);

	/*�ꉞ����������Draw��Uninit���Ăׂ�OK*/
	static void Init();
	static void Update();
	static void Draw();
	static void Uninit();

};