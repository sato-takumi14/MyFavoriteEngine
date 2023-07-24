#pragma once


class Post
{
private:

	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	//ここに	シェーダー関連の変数を追加
	ID3D11VertexShader* m_VertexShader{}; //頂点シェーダーオブジェクト
	ID3D11PixelShader* m_PixelShader{}; //ピクセルシェーダーオブジェクト
	ID3D11InputLayout* m_VertexLayout{}; //頂点レイアウトオブジェクト


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};