#include"main.h"
#include"renderer.h"
#include"camera.h"

void Camera::Init()
{
	m_Position = Vector3(0.0f, 5.0f, -10.0f);
	m_Target = Vector3(0.0f, 0.0f, 0.0f);
}

void Camera::Update()
{

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
}