
#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureNormalMap : register(t1);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	//このピクセルの法線マップのデータRGBA値を取得
	float4 normalMap = g_TextureNormalMap.Sample(g_SamplerState, In.TexCoord);

	//スケーリング
	//取得したRGBA値をベクトル情報XYWZとして展開する
	normalMap = normalMap * 2.0f - 1.0f;

	float4 n = normalize(In.Normal);
	float4 t = normalize(In.Tangent);
	float4 b = normalize(In.Binormal);
	//展開したテクスチャデータを法線用変数へ入れ替え
	float4 normal;
	//normal.x = -normalMap.r;
	//normal.y = normalMap.b;
	//normal.z = normalMap.g;
	//normal.w = 0.0f;
	//normal = normalize(normal);//正規化

	normal.xyz = t.xyz * normalMap.x + b.xyz * normalMap.y + n.xyz * normalMap.z;
	normal.w = 0.0f;
	normal = normalize(normal);

	//光源の向きと回転済みの法線とで内積を計算し、符号を反転して輝度を求める
	float light = -dot(Light.Direction.xyz, normal.xyz);
	//飽和演算(0.0～1.0の値にクランプする)
	light = saturate(light);

	//テクスチャから色をサンプリングする
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	//テクスチャの色に輝度を乗算する
	outDiffuse.rgb *= light;
	//透明度は輝度に影響しないのでそのまま使う
	outDiffuse.a *= In.Diffuse.a;


	//ブリンフォン鏡面反射
	//視線ベクトルを作成する（カメラからピクセルへ向かうベクトル）
	float3 evev = In.WorldPosition.xyz - camera.Position.xyz;
	evev = normalize(evev);
	//ハーフベクトルを作成する（視線ベクトル＋ライトベクトル）
	float3 halfv = evev + Light.Direction.xyz;
	halfv = normalize(halfv);

	float specular = -dot(halfv, normal.xyz);
	saturate(specular);
	specular = pow(specular, 30);
	outDiffuse.rgb = saturate(outDiffuse.rgb + specular);
}
