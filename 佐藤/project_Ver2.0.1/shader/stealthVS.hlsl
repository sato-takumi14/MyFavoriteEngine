
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

	//入力されたUV座標を出力先へ代入する
    float2 tex = Out.Position.xy; //wvp行列の乗算結果をそのまま使う
	
	//正規化したデバイス座標を計算する
	tex.x = Out.Position.x / Out.Position.w;//透視変換
	tex.y = Out.Position.y / Out.Position.w;//透視変換

	//正規化デバイス座標をテクスチャ座標へ変換
	tex.x = (tex.x * 0.5f) + 0.5f + 0.03f;//最後の部分が屈折率
	tex.y = (-tex.y * 0.5f) + 0.5f + 0.03f;//完全に見えなくなるのを防ぐため座標をずらす

	Out.TexCoord = saturate(tex);//画面外にならないように補正

	//頂点の法線をワールド行列で変換する
	float4 worldNormal, normal;

	normal = float4(In.Normal.xyz, 0.0);
	worldNormal = mul(normal, World);
	worldNormal = normalize(worldNormal);
	Out.Normal = worldNormal;
    Out.Tangent = float4(0.0, 0.0, 0.0, 0.0);
    Out.Binormal = float4(0.0, 0.0, 0.0, 0.0);
	
	//頂点カラーはそのままコピー
	Out.Diffuse = In.Diffuse;

    Out.WorldPosition = mul(In.Position, World);
}
