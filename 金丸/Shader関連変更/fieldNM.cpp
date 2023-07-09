
#include "main.h"
#include "renderer.h"
#include "fieldNM.h"
#include "input.h"
#include "material.h"



void FieldNM::Init()
{
	int yoko = 5;//���̃|���S���̕�����
	int tate = 5;//�c�̃|���S���̕�����
	float takasa = 0.0f;//�����_���ō쐬���鍂���̍ő�l
	float sizeX = 4.0f;//�|���S���̉���
	float sizeZ = 4.0f;//�|���S���̍���

	//�K�v�Ȓ��_�����v�Z����
	m_numVertex = (yoko + 1) * (tate + 1);
	m_numIndex = (yoko + 1) * 2 * tate + (tate - 1) * 2;

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * m_numVertex;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Renderer::GetDevice()->CreateBuffer(&bd, NULL, &m_VertexBuffer);

	// �C���f�b�N�X�o�b�t�@����
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(unsigned short) * m_numIndex;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Renderer::GetDevice()->CreateBuffer(&bd, NULL, &m_IndexBuffer);

	{//���_�o�b�t�@�̒��g�𖄂߂�

		// ���_�o�b�t�@�ւ̃|�C���^���擾
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

		for (int y = 0; y < (tate + 1); y++)
		{
			for (int x = 0; x < (yoko + 1); x++)
			{
				int i = y * (yoko + 1) + x;

				float height = ((float)rand() / RAND_MAX) * takasa;
				// ���_���W�̐ݒ�
				pVtx[i].Position = D3DXVECTOR3(-(yoko / 2.0f) * sizeX + x * sizeX, height, (tate / 2.0f) * sizeZ - y * sizeZ);
				// UV�l�̐ݒ�
				pVtx[i].TexCoord = D3DXVECTOR2(x, y);


				D3DXVECTOR3 vUP(0.0f, 0.0f, 1.0f);
				// �@���̐ݒ�
				pVtx[i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//�ڃx�N�g���̐ݒ�
				D3DXVec3Cross(&pVtx[i].Tangent, &pVtx[i].Normal, &vUP);
				//�]�@���x�N�g���̐ݒ�
				D3DXVec3Cross(&pVtx[i].Binormal, &pVtx[i].Normal, &pVtx[i].Tangent);

				// ���_�J���[�̐ݒ�
				pVtx[i].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
	}

	{//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�

		// �C���f�b�N�X�o�b�t�@�̃|�C���^���擾
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_IndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		unsigned short* pIdx = (unsigned short*)msr.pData;

		int idx = 0;

		for (int y = 0; y < tate; y++)
		{
			for (int x = 0; x < (yoko + 1); x++)
			{
				pIdx[idx] = (yoko + 1) + x + (yoko + 1) * y;
				idx++;
				pIdx[idx] = 0 + x + (yoko + 1) * y;
				idx++;
			}

			if (y < (tate - 1))
			{
				pIdx[idx] = yoko + (yoko + 1) * y;
				idx++;
				pIdx[idx] = (yoko + 1) * 2 + (yoko + 1) * y;
				idx++;
			}
		}

		Renderer::GetDeviceContext()->Unmap(m_IndexBuffer, 0);
	}

	// �e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/field004.jpg",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);

	// �e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/fieldNormal.png",
		NULL,
		NULL,
		&m_TextureNormalMap,
		NULL);
	assert(m_TextureNormalMap);

	AddComponent<Matelial>()->Init("shader\\normalMappingVS.cso", "shader\\normalMappingPS.cso");
}


void FieldNM::Uninit()
{

	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_Texture->Release();
	m_TextureNormalMap->Release();

	GameObject::Uninit();
}


void FieldNM::Update()
{
	if (Input::GetKeyPress('R'))
		m_Rotation.x -= 0.1f;
	if (Input::GetKeyPress('F'))
		m_Rotation.x += 0.1f;

	if (Input::GetKeyPress('Q'))
		m_Rotation.y -= 0.1f;
	if (Input::GetKeyPress('E'))
		m_Rotation.y += 0.1f;

	GameObject::Update();
}


void FieldNM::Draw()
{
	// �}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	GameObject::Draw();

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�ݒ�
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);
	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &m_TextureNormalMap);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	Renderer::GetDeviceContext()->DrawIndexed(m_numIndex, 0, 0);
}