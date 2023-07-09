
#include "common.hlsl"

static const float pi = 3.1415926535f;

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    outDiffuse = float4(0.0f, 0.0f, 0.0f, 1.0f);
     
    float nowHp = param.Hp.x;
    float maxHp = param.Hp.y;
    float oldHp = param.Hp.z;

	//UV�l����s�N�Z���ւ̃X�P�[���ϊ����s��
	//=================�l�p==================================
	float gauge = In.TexCoord.x * maxHp;

	//HP�Q�[�W�̃O���[�������쐬����
	outDiffuse.rgb += param.LostColor.rgb * step(oldHp, gauge);
	//HP�Q�[�W�̗Ε������쐬����
	outDiffuse.rgb += param.BaseColor.rgb * (1.0f - step(nowHp, gauge));
	//HP�Q�[�W�̐Ԃ��������쐬����
	outDiffuse.rgb += param.DiffColor.rgb * (1.0f - step(oldHp, gauge)) * step(nowHp, gauge);
	//========================================================
	//=================��=======================================
	////UV�l�����炷
 //   float2 uv = In.TexCoord - 0.5f;
	////�p�x�����
 //   float angle = atan2(uv.x, uv.y);
	////atan�ŕԂ��Ă���̂�-3.14...�`3.14...�Ȃ̂�0�`2�΂ɂ���
 //   angle += pi;
	
 //   float gauge = frac(angle * 0.5f / pi) * maxHp;
 //   outDiffuse.rgb += param.LostColor.rgb * step(oldHp, gauge);
 //   outDiffuse.rgb += param.BaseColor.rgb * (1.0f - step(nowHp, gauge));
 //   outDiffuse.rgb += param.DiffColor.rgb * (1.0f - step(oldHp, gauge)) * step(nowHp, gauge);

 //   float dist = length(uv) / 0.5f;
 //   outDiffuse.a = (1.0f - step(1.0f, dist)) * step(0.3, dist);
	//==========================================================
}


