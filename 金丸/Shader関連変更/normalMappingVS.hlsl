
#include "common.hlsl"



void main(in VS_IN In, out PS_IN Out)
{
	matrix wvp;//matrix�^�̕ϐ�wvp���`����

	//wvp = ���[���h�ϊ��s��~�r���[�ϊ��s��
	wvp = mul(World, View);
	//wvp = wvp �~ �v���W�F�N�V�����ϊ��s��
	wvp = mul(wvp, Projection);

	//���͂��ꂽ���_���W��ϊ����ďo�͐�֑������
	Out.Position = mul(In.Position, wvp);

	
	float4 worldNormal, normal;

	//Normal
	//���͂��ꂽ�@����񂩂��]��񂾂������o�����߂̉������Ƃ���W���[���ɂ���
	normal = float4(In.Normal.xyz, 0.0);
	//�@�������[���h�ϊ�����
	worldNormal = mul(normal, World);

	Out.Normal = normalize(worldNormal);

	//Tangent
	normal = float4(In.Tangent.xyz, 0.0);
	worldNormal = mul(normal, World);
	Out.Tangent = normalize(worldNormal);

	//Binormal
	normal = float4(In.Binormal.xyz, 0.0);
	worldNormal = mul(normal, World);
	Out.Binormal = normalize(worldNormal);


	//���_�J���[�͂��̂܂܃R�s�[
	Out.Diffuse = In.Diffuse;

	//���͂��ꂽUV���W���o�͐�֑������
	Out.TexCoord = In.TexCoord;

	
}
