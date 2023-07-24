
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

	//���͂��ꂽUV���W���o�͐�֑������
    float2 tex = Out.Position.xy; //wvp�s��̏�Z���ʂ����̂܂܎g��
	
	//���K�������f�o�C�X���W���v�Z����
	tex.x = Out.Position.x / Out.Position.w;//�����ϊ�
	tex.y = Out.Position.y / Out.Position.w;//�����ϊ�

	//���K���f�o�C�X���W���e�N�X�`�����W�֕ϊ�
	tex.x = (tex.x * 0.5f) + 0.5f + 0.03f;//�Ō�̕��������ܗ�
	tex.y = (-tex.y * 0.5f) + 0.5f + 0.03f;//���S�Ɍ����Ȃ��Ȃ�̂�h�����ߍ��W�����炷

	Out.TexCoord = saturate(tex);//��ʊO�ɂȂ�Ȃ��悤�ɕ␳

	//���_�̖@�������[���h�s��ŕϊ�����
	float4 worldNormal, normal;

	normal = float4(In.Normal.xyz, 0.0);
	worldNormal = mul(normal, World);
	worldNormal = normalize(worldNormal);
	Out.Normal = worldNormal;
    Out.Tangent = float4(0.0, 0.0, 0.0, 0.0);
    Out.Binormal = float4(0.0, 0.0, 0.0, 0.0);
	
	//���_�J���[�͂��̂܂܃R�s�[
	Out.Diffuse = In.Diffuse;

    Out.WorldPosition = mul(In.Position, World);
}
