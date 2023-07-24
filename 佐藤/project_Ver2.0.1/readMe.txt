※注意点
トランスフォームを当たり判定の時に使用しているのでゲームオブジェクトのInitを呼び出してからでないとエラーが出る

追加クラス
******************************************************************
Collision:シングルトン

private:変数
m_Circle	CircleColliderをセットするlist型変数
m_Box		BoxColliderをセットするlist型変数

private:関数
HitCheckCircle(Collider* hit, Collider* washit)		円の当たり判定
HitCheckBox(Collider* hit, Collider* washit)		四角の当たり判定

OnCollisionEnter()	Unityと同じ機能
OnCollisionExit()	Unityと同じ機能

public:関数
Update()	OnCollisoinEnterとOnCollisionExit()を呼び出す
		その後ゲームオブジェクトがデストロイされるならprivate変数のゲームオブジェクトを消す
Uninit()	変数のリストを全てクリア

SetCircleCollider(Collider* collider)	CircleColliderセット関数
SetBoxCollider(Collider* collider)	BoxColliderセット関数

******************************************************************
Collider:Component継承

private:変数
class GameObject* m_Object{};		このコンポーネントがついているオブジェクトのポインタ変数
class Transform* m_Transform{};		このコンポーネントがついているオブジェクトのトランスフォームのポインタ変数
float m_Radius{};			当たり判定する際の大きさ
Vector3 m_Offset{};			当たり判定をずらすとき用の変数
list<GameObject*> m_Objects;		当たっているオブジェクトを所持するリスト


public:関数
virtual void Init(GameObject* obj, Transform* transform, Vector3 offset, float radius)	
初期でもっておの最低限の変数をセットする

void Update()override	private変数のリストにある分だけGameObjectクラスのOnCollisionStayを呼び出す
void Uninit()override	m_Objectsのクリア

void OnCollisionEnter(GameObject* obj)	当たっている際に呼び出され当たった最初の時に当たり判定用の関数が呼び出される
void OnCollisionExit(GameObject* obj)	当たっていたオブジェクトが離れた時に呼び出される　リストのオブジェクトをリストから削除する

ゲット関数
GameObject* GetGameObject()
const bool GetDestroy()const;
Vector3 GetPosition()const;
const float GetRadius()const { return m_Radius; }

******************************************************************
CircleCollider

public:関数
void Init(GameObject* obj, Transform* transform, Vector3 offset, float radius)override
中でColliderのInitを呼び出してその後にCollisinクラスのCircleCollider用の変数にセットする

******************************************************************
BoxCollider

public:関数
void Init(GameObject* obj, Transform* transform, Vector3 offset, float radius)override
中でColliderのInitを呼び出してその後にCollisinクラスのBoxCollider用の変数にセットする

******************************************************************
Enemy:GameObject継承

当たり判定用の確認用に作成

******************************************************************
dbgstream

使い方
cdbg << "ここに文字などを入力しておく" << endl;
基本的にiostreamのcoutの使い方と同じ

実行中に下の出力のところに↑の文字などが出てくる

******************************************************************
Debug:シングルトン

使い方
マクロ
TO_STRING(変数名)	変数名を文字列に変換
FUNCTIONNAME		現在実行中の関数名の文字列にして取得

public:関数

Update()		加えるfloatの値を増減させる
Uninit()		unorderd_mapに格納されているデータをdebug.txtに出力する

Position(Vector3)	
引数のVector3を「cdbg << "Pos：x " << pos.x << " y " << pos.y << " z " << pos.z << endl」と表示

Rotation(Vector3)	
引数のVector3を「cdbg << "Rot：x " << rot.x << " y " << rot.y << " z " << rot.z << endl」と表示

Scale(Vector3)		
引数のVector3を「cdbg << "Scale：x " << scale.x << " y " << scale.y << " z " << scale.z << endl」と表示

MethodName(const char name[], string tag)
name	メソッド名※上のFUNCTIONNAMEを引数にする
tag	オブジェクトが持っているタグ

DestroyAlert(string tag)
オブジェクトをデリートするときに呼ぶとわかりやすくなる

Adjustment((float or int)*target, const char function[], string tag, string variable)
target		実行中に変更する変数
function	FUNCTIONNAMEを引数にする
tag		ゲームオブジェクトが持っているタグ
variable	TO_STRING(target) targetを引数にTO_STRINGを使用

* ゲームオブジェクトのタグ名
* 呼び出された場所の関数名
* 変更した変数名
* 最終的な変数値

がasset\\debug.txtファイルに出力される
引数がtargetだけのものは出力しない場合使う

******************************************************************

変更クラス
******************************************************************
gameObject

private:変数

string m_Tag	ゲームオブジェクトを識別するためのタグ
float m_Radius	当たり判定する大きさ

public:関数
const float GetRadius()const	当たり判定する大きさを取得 
const bool GetDestroy()const	破壊するかを取得

virtual void OnCollisionEnter(GameObject* obj)	最初に当たった時に呼び出される
virtual void OnCollisionExit(GameObject* obj)	当たっていたオブジェクトが離れた時に呼び出される
virtual void OnCollisionStay(GameObject* obj)	当たり続けているオブジェクトがあるとき呼び出される

******************************************************************
