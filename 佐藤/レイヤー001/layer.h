#pragma once

#include<list>
#include<unordered_map>
#include<algorithm>
#include<string>

#include"gameObject.h"

using namespace std;

/****************************************************************************************
*
*		制作者：佐藤匠
*		作成日：07/11
*		クラス名：LayerName
*
*****************************************************************************************
* レイヤー名ごとに格納するクラス
*****************************************************************************************/

class LayerName
{
private:

	string m_Name{};						//レイヤー名
	list<GameObject*> m_GameObjects;		//ゲームオブジェクトを格納

public:

	LayerName() {}

	//レイヤー名をセットするコンストラクタ
	LayerName(string name) : m_Name(name) {}

	//ゲームオブジェクトセット
	void AddGameObject(GameObject* obj) { m_GameObjects.push_back(obj); }

	//レイヤー名取得
	string GetLayerName() { return m_Name; }

	//初期化処理
	void Init() {
		for (auto& obj : m_GameObjects) {
			obj->Init();
		}
	}

	//更新処理
	void Update() {}

	//描画処理
	void Draw() {
		for (auto& obj : m_GameObjects) {
			obj->Draw();
		}
	}

	//終了処理
	void Uninit() {
		m_GameObjects.clear();
	}

};

/****************************************************************************************
*
*		制作者：佐藤匠
*		作成日：07/11
*		クラス名：Layer
*
*****************************************************************************************
* 描画順番を管理するクラス
*****************************************************************************************/

class Layer
{
private:

	static unordered_map<string, LayerName*> m_Layer;	//各レイヤー
	static int m_Index;									//現在のレイヤー番号

public:

	//レイヤーにゲームオブジェクトをセット
	static void SetLayer(string name, GameObject* obj);

	//新規レイヤー追加
	static void AddLayer(string name);

	/*一応書いたけどDrawとUninitを呼べばOK*/
	static void Init();
	static void Update();
	static void Draw();
	static void Uninit();

};