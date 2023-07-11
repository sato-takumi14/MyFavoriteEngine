
#include "layerOrder.h"

unordered_map<int, Order> LayerOrder::m_Order;
int LayerOrder::m_Index = 0;

void LayerOrder::SetLayer(Order order)
{
	m_Order[m_Index++] = order;
}

void LayerOrder::ChangeLayerName(Order order, int number)
{
	if (order.id < 0)return;

	for (int i = 0; i < m_Index; i++) {
		if (order.name == m_Order[i].name) {
			m_Order[i].id = number;
		}
		else if (number <= m_Order[i].id) {

			m_Order[i].id++;
			/*if (order.id == m_Order[i].id) {
				m_Order[i].id++;
			}*/
		}
		
	}



}

string LayerOrder::GetLayerName(int id)
{
	for (int i = 0; i < m_Index; i++) {
		if (m_Order[i].id == id) {
			return m_Order[i].name;
		}
	}

	return "";
}

Order LayerOrder::GetOrder(string name)
{

	for (int i = 0; i < m_Index; i++) {
		if (name == m_Order[i].name) {
			return m_Order[i];
		}
	}

	Order order{};
	order.id = -1;
	return order;
}
