#pragma once
#include "component.h"


// マテリアル構造体
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL					Material;
	char						TextureName[256];
	ID3D11ShaderResourceView*	Texture;

};


// 描画サブセット構造体
struct SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	MODEL_MATERIAL	Material;
};


// モデル構造体
struct MODEL
{
	VERTEX_3D		*VertexArray;
	unsigned int	VertexNum;

	unsigned int	*IndexArray;
	unsigned int	IndexNum;

	SUBSET			*SubsetArray;
	unsigned int	SubsetNum;
};





class Model:public Component
{
private:

	ID3D11Buffer*	m_VertexBuffer;
	ID3D11Buffer*	m_IndexBuffer;

	char* m_File;
	SUBSET*	m_SubsetArray;
	unsigned int	m_SubsetNum;

	void LoadObj( const char *FileName, MODEL *Model );
	void LoadMaterial( const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned int *MaterialNum );

public:

	void Draw();

	void Load( const char *FileName );
	void Unload();
	const char* GetFile() { return m_File; }

	void CalcTangentAndBinormal(D3DXVECTOR3* p0, D3DXVECTOR2* uv0,
		D3DXVECTOR3* p1, D3DXVECTOR2* uv1,
		D3DXVECTOR3* p2, D3DXVECTOR2* uv2,
		D3DXVECTOR3* outTangent, D3DXVECTOR3* outBinormal);
};