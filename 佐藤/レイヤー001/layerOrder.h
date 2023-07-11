#pragma once

#include<string>
#include<unordered_map>

using namespace std;

//レイヤー順番情報
typedef struct {
	string name;
	int id;
}Order;

class LayerOrder
{
private:

	static unordered_map<int, Order> m_Order;	//レイヤー順番情報
	static int m_Index;							//現在レイヤー順番情報数

public:

	//レイヤー順番情報セット
	static void SetLayer(Order order);

	/*レイヤー順番変更
	* 引数1：変更する順番情報
	* 引数2：変更する順番情報をnumberの番号にする*/
	static void ChangeLayerName(Order order, int number);

	/*レイヤー順番情報のレイヤー名取得
	* 引数1：レイヤー順番情報のidの番号*/
	static string GetLayerName(int id);

	/*レイヤー順番情報取得
	* 引数1：レイヤー順番情報のレイヤー名*/
	static Order GetOrder(string name);

};