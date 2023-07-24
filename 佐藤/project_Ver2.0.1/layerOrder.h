#pragma once

#include<string>
#include<unordered_map>

using namespace std;

//���C���[���ԏ��
typedef struct {
	string name;
	int id;
}Order;

class LayerOrder
{
private:

	static unordered_map<int, Order> m_Order;	//���C���[���ԏ��
	static int m_Index;							//���݃��C���[���ԏ��

public:

	//���C���[���ԏ��Z�b�g
	static void SetLayer(Order order);

	/*���C���[���ԕύX
	* ����1�F�ύX���鏇�ԏ��
	* ����2�F�ύX���鏇�ԏ���number�̔ԍ��ɂ���*/
	static void ChangeLayerName(Order order, int number);

	/*���C���[���ԏ��̃��C���[���擾
	* ����1�F���C���[���ԏ���id�̔ԍ�*/
	static string GetLayerName(int id);

	/*���C���[���ԏ��擾
	* ����1�F���C���[���ԏ��̃��C���[��*/
	static Order GetOrder(string name);

};