
#include "common.hlsl"



void main(in VS_IN In, out PS_IN Out)
{
	matrix wvp;//matrix型の変数wvpを定義する

	//wvp = ワールド変換行列×ビュー変換行列
	wvp = mul(World, View);
	//wvp = wvp × プロジェクション変換行列
	wvp = mul(wvp, Projection);

	//入力された頂点座標を変換して出力先へ代入する
	Out.Position = mul(In.Position, wvp);

	
	float4 worldNormal, normal;

	//Normal
	//入力された法線情報から回転情報だけ抜き出すための下準備としてWをゼロにする
	normal = float4(In.Normal.xyz, 0.0);
	//法線をワールド変換する
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


	//頂点カラーはそのままコピー
	Out.Diffuse = In.Diffuse;

	//入力されたUV座標を出力先へ代入する
	Out.TexCoord = In.TexCoord;

	
}
