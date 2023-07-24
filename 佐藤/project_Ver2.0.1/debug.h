#pragma once

/******************************************************************************************************
*
*		[debug.h]
*																	����ҁF������
*																	�쐬���F07/24
*
*******************************************************************************************************
* Debug�N���X : ��{�I�ȃf�o�b�O�̏o�͂��y�ɂ��邽�߂̃N���X
* Adjustment�̉��̓���g���ƃf�o�b�O�e�L�X�g��
* �Q�[���I�u�W�F�N�g�̃^�O��
* �Ăяo���ꂽ�ꏊ�̊֐���
* �ύX�����ϐ���
* �ŏI�I�ȕϐ��l
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

	/*�ϐ������s���ɕύX����*/
	static void Adjustment(float* target);
	static void Adjustment(int* target);

	/*�f�o�b�O�e�L�X�g�ɏo��*/
	static void Adjustment(float* target, const char function[], string tag, string variable);
	static void Adjustment(int* target, const char function[], string tag, string variable);

};
