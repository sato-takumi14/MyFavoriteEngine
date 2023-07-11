
#include "layer.h"
#include"layerOrder.h"

unordered_map<string, LayerName*> Layer::m_Layer;
int Layer::m_Index = 0;

void Layer::SetLayer(string name, GameObject* obj)
{
	m_Layer[name]->AddGameObject(obj);
}

void Layer::AddLayer(string name)
{
	m_Layer[name] = new LayerName(name);
	LayerOrder::SetLayer(Order{ name,m_Index });
	m_Index++;
}

void Layer::Init()
{
	for (int i = 0; i < m_Index; i++) {
		m_Layer[LayerOrder::GetLayerName(i)]->Init();
	}
}

void Layer::Update()
{
	for (int i = 0; i < m_Index; i++) {
		m_Layer[LayerOrder::GetLayerName(i)]->Update();
	}
}

void Layer::Draw()
{
	for (int i = 0; i < m_Index; i++) {
		m_Layer[LayerOrder::GetLayerName(i)]->Draw();
	}
}

void Layer::Uninit()
{
	for (int i = 0; i < m_Index; i++) {
		m_Layer[LayerOrder::GetLayerName(i)]->Uninit();
	}
	m_Layer.clear();
	m_Index = 0;
}
