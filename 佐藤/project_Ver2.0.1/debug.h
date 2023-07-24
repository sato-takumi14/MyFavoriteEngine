#pragma once

/******************************************************************************************************
*
*		[debug.h]
*																	制作者：佐藤匠
*																	作成日：07/24
*
*******************************************************************************************************
* Debugクラス : 基本的なデバッグの出力を楽にするためのクラス
* Adjustmentの下の二つを使うとデバッグテキストに
* ゲームオブジェクトのタグ名
* 呼び出された場所の関数名
* 変更した変数名
* 最終的な変数値
*******************************************************************************************************/

#include<string>
#include<unordered_map>

//#define GET_NAME(n,sz) strcpy(sz,#n)
#define TO_STRING(VariableName) # VariableName
#define FUNCTIONNAME __func__

using namespace std;

typedef struct {

	char newline1;
	char tag[30];
	char newline2;
	char function[100];
	char newline3;
	char variable[256];
	char newline4;
	char data[20];
	char newline5;

}DebugData;

typedef struct {

	string tag;
	string function;
	string variable;
	float data;

}HoldData;



class Debug
{
private:

#if _DEBUG

	static int m_IntAdd;
	static float m_FloatAdd;

	static float m_SetFloat;

	static bool m_RightFlag;
	static bool m_LeftFlag;

	static unordered_map<string, HoldData> m_DebugData;

#endif // _DEBUG



public:

	static void Update();
	static void Uninit();

	static void Position(Vector3 pos);
	static void Rotation(Vector3 rot);
	static void Scale(Vector3 scale);

	static void MothodName(const char name[], string tag);

	static void DestroyAlert(string tag);

	/*変数を実行中に変更する*/
	static void Adjustment(float* target);
	static void Adjustment(int* target);

	/*デバッグテキストに出力*/
	static void Adjustment(float* target, const char function[], string tag, string variable);
	static void Adjustment(int* target, const char function[], string tag, string variable);

};
