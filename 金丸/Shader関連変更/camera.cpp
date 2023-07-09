#include"main.h"
#include"renderer.h"
#include"camera.h"
#include "input.h"

void Camera::Init()
{
	m_Position = Vector3(0.0f, 5.0f, -10.0f);
	m_Target = Vector3(0.0f, 0.0f, 0.0f);
	m_Param = D3DXVECTOR4(10.0f, 50.0f, 3.5f, 0.0f);
	m_FogColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_GroundFogColor = D3DXCOLOR(0.5f, 0.0f, 0.5f, 1.0f);
}

void Camera::Update()
{
	if (Input::GetKeyPress('H'))
		m_Position.x -= 0.1f;

	if (Input::GetKeyPress('K'))
		m_Position.x += 0.1f;

	if (Input::GetKeyPress('U'))
		m_Position.z += 0.1f;

	if (Input::GetKeyPress('J'))
		m_Position.z -= 0.1f;

	if (Input::GetKeyPress('Y'))
		m_Position.y += 0.1f;

	if (Input::GetKeyPress('I'))
		m_Position.y -= 0.1f;

	/*if (Input::GetKeyPress('R'))
		m_FogColor.r += 0.01f;

	if (Input::GetKeyPress('G'))
		m_FogColor.g += 0.01f;

	if (Input::GetKeyPress('B'))
		m_FogColor.b += 0.01f;

	if (Input::GetKeyPress('E'))
		m_FogColor.r -= 0.01f;

	if (Input::GetKeyPress('F'))
		m_FogColor.g -= 0.01f;

	if (Input::GetKeyPress('V'))
		m_FogColor.b -= 0.01f;*/

		//フォグパラメーター更新

	if (Input::GetKeyPress('Z'))
		m_Param.x += 1.0f;
	if (Input::GetKeyPress('X'))
		m_Param.x -= 1.0f;

	if (Input::GetKeyPress('C'))
		m_Param.y += 1.0f;
	if (Input::GetKeyPress('V'))
		m_Param.y -= 1.0f;

	if (Input::GetKeyPress('B'))
		m_Param.z += 0.2f;
	if (Input::GetKeyPress('N'))
		m_Param.z -= 0.2f;
}

void Camera::Draw()
{
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMatrix, (D3DXVECTOR3*)&m_Position, (D3DXVECTOR3*)&m_Target, (D3DXVECTOR3*)&up);

	Renderer::SetViewMatrix(&m_ViewMatrix);

	//プロジェクションマトリックス設定
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f,
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);

	CAMERA camera;
	D3DXVECTOR4 cpos = D3DXVECTOR4(m_Position.x, m_Position.y, m_Position.z, 1.0f);
	camera.Position = cpos;
	camera.FogParam.x = m_Param.x;//FogStart
	camera.FogParam.y = m_Param.y;//FogEnd
	camera.FogParam.z = m_Param.z;//FogHeight
	camera.FogColor = D3DXCOLOR(m_FogColor.r, m_FogColor.g, m_FogColor.b, m_FogColor.a);
	camera.GroundFogColor = D3DXCOLOR(m_GroundFogColor.r, m_GroundFogColor.g, m_GroundFogColor.b, m_GroundFogColor.a);
	Renderer::SetCamera(camera);
}