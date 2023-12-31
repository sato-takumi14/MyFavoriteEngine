#pragma once

struct VERTEX_3D
{
    D3DXVECTOR3 Position;
    D3DXVECTOR3 Normal;
	D3DXVECTOR3 Tangent;
	D3DXVECTOR3 Binormal;
    D3DXVECTOR4 Diffuse;
    D3DXVECTOR2 TexCoord;
};

struct MATERIAL
{
	D3DXCOLOR	Ambient;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Specular;
	D3DXCOLOR	Emission;
	float		Shininess;
	BOOL		TextureEnable;
	float		Dummy[2];
};

struct LIGHT
{
	BOOL		Enable;
	BOOL		Dummy[3];
	D3DXVECTOR4	Direction;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Ambient;
};

struct CAMERA
{
	D3DXVECTOR4	Position;
	D3DXVECTOR4 FogParam;//x:FogStart,y:FogEnd,z:FogHeight
	D3DXCOLOR	FogColor;
	D3DXCOLOR	GroundFogColor;
};


struct PARAMETER
{
	D3DXVECTOR4 hitpoint;
	D3DXCOLOR	baseColor;
	D3DXCOLOR	lostColor;
	D3DXCOLOR	diffColor;
};


class Renderer
{
private:

	static D3D_FEATURE_LEVEL       m_FeatureLevel;

	static ID3D11Device*           m_Device;
	static ID3D11DeviceContext*    m_DeviceContext;
	static IDXGISwapChain*         m_SwapChain;
	static ID3D11RenderTargetView* m_RenderTargetView;
	static ID3D11DepthStencilView* m_DepthStencilView;

	static ID3D11Buffer*			m_WorldBuffer;
	static ID3D11Buffer*			m_ViewBuffer;
	static ID3D11Buffer*			m_ProjectionBuffer;
	static ID3D11Buffer*			m_MaterialBuffer;
	static ID3D11Buffer*			m_LightBuffer;
	static ID3D11Buffer*            m_CameraBuffer;
	static ID3D11Buffer*            m_ParameterBuffer;

	static ID3D11DepthStencilState* m_DepthStateEnable;
	static ID3D11DepthStencilState* m_DepthStateDisable;

	static ID3D11BlendState*		m_BlendState;
	static ID3D11BlendState*		m_BlendStateATC;

	static ID3D11RenderTargetView* m_PPRenderTargetView;
	static ID3D11ShaderResourceView* m_PPShaderResourceView;

	static ID3D11RenderTargetView* m_BGRenderTargetView;
	static ID3D11ShaderResourceView* m_BGShaderResourceView;
public:
	static void Init();
	static void Uninit();
	static void Begin();
	static void End();

	static void SetDepthEnable(bool Enable);
	static void SetATCEnable(bool Enable);
	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(D3DXMATRIX* WorldMatrix);
	static void SetViewMatrix(D3DXMATRIX* ViewMatrix);
	static void SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix);
	static void SetMaterial(MATERIAL Material);
	static void SetLight(LIGHT Light);

	static void SetCamera(CAMERA Camera);
	static void SetParameter(PARAMETER param);

	static ID3D11Device* GetDevice( void ){ return m_Device; }
	static ID3D11DeviceContext* GetDeviceContext( void ){ return m_DeviceContext; }



	static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);

	static ID3D11ShaderResourceView* GetPPTexture(){return m_PPShaderResourceView;}//レンダリングテクスチャのポインタを取得
	//レンダリングターゲットをテクスチャへ切り替える関数
	static void BeginPP()
	{
		//レンダ―ターゲットとZバッファのセット
		m_DeviceContext->OMSetRenderTargets(1, &m_PPRenderTargetView,
			m_DepthStencilView);
		//わかりやすいようにレンダ―ターゲットを緑でクリアしておく
		float ClearColor[4] = { 0.0f, 0.5f, 0.0f, 1.0f };
		m_DeviceContext->ClearRenderTargetView(m_PPRenderTargetView,
			ClearColor);
		//Zバッファのクリア
		m_DeviceContext->ClearDepthStencilView(m_DepthStencilView,
			D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	static ID3D11ShaderResourceView* GetBGTexture() { return m_BGShaderResourceView; }//レンダリングテクスチャのポインタを取得

	static void BeginBG()
	{
		//レンダーターゲットとZバッファのセット
		m_DeviceContext->OMSetRenderTargets(1, &m_BGRenderTargetView, m_DepthStencilView);

		//分かりやすいようにレンダーターゲットを緑でクリアしておく
		float ClearColor[4] = { 0.0f,0.5f,0.0f,1.0f };
		m_DeviceContext->ClearRenderTargetView(m_BGRenderTargetView, ClearColor);

		//Zバッファのクリア
		m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

};
