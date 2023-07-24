
#include "common.hlsl"

static const float pi = 3.1415926535f;

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    outDiffuse = float4(0.0f, 0.0f, 0.0f, 1.0f);
     
    float nowHp = param.Hp.x;
    float maxHp = param.Hp.y;
    float oldHp = param.Hp.z;

	//UV値からピクセルへのスケール変換を行う
	//=================四角==================================
	float gauge = In.TexCoord.x * maxHp;

	//HPゲージのグレー部分を作成する
	outDiffuse.rgb += param.LostColor.rgb * step(oldHp, gauge);
	//HPゲージの緑部分を作成する
	outDiffuse.rgb += param.BaseColor.rgb * (1.0f - step(nowHp, gauge));
	//HPゲージの赤い部分を作成する
	outDiffuse.rgb += param.DiffColor.rgb * (1.0f - step(oldHp, gauge)) * step(nowHp, gauge);
	//========================================================
	//=================丸=======================================
	////UV値をずらす
 //   float2 uv = In.TexCoord - 0.5f;
	////角度を取る
 //   float angle = atan2(uv.x, uv.y);
	////atanで返ってくるのが-3.14...～3.14...なので0～2πにする
 //   angle += pi;
	
 //   float gauge = frac(angle * 0.5f / pi) * maxHp;
 //   outDiffuse.rgb += param.LostColor.rgb * step(oldHp, gauge);
 //   outDiffuse.rgb += param.BaseColor.rgb * (1.0f - step(nowHp, gauge));
 //   outDiffuse.rgb += param.DiffColor.rgb * (1.0f - step(oldHp, gauge)) * step(nowHp, gauge);

 //   float dist = length(uv) / 0.5f;
 //   outDiffuse.a = (1.0f - step(1.0f, dist)) * step(0.3, dist);
	//==========================================================
}


