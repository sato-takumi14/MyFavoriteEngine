cbuffer WorldBuffer : register(b0)
{
	matrix World;
}
cbuffer ViewBuffer : register(b1)
{
	matrix View;
}
cbuffer ProjectionBuffer : register(b2)
{
	matrix Projection;
}




struct MATERIAL
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float4 Emission;
	float Shininess;
	float3 Dummy;
};

cbuffer MaterialBuffer : register(b3)
{
	MATERIAL Material;
}


struct LIGHT
{
    bool Enable;
    bool3 Dummy;
    float4 Direction;
    float4 Diffuse;
    float4 Ambient;
};

cbuffer LightBuffer : register(b4)
{
	LIGHT Light;
}

struct Camera
{
    float4 Position; //ÉJÉÅÉâÇÃç¿ïWÇéÛÇØéÊÇÈ
    float4 FogParam; //x:FogStart,y:FogEnd,z:FogHeight
    float4 FogColor;
    float4 GroundFogColor;
};

cbuffer CameraBuffer : register(b5)
{
    Camera camera;
}

struct PARAMETER
{
    float4 Hp;
    float4 BaseColor;
    float4 LostColor;
    float4 DiffColor;
};

cbuffer ParamBuffer : register(b6)
{
    PARAMETER param;
}

struct VS_IN
{
    float4 Position   : POSITION0;
    float4 Normal     : NORMAL0;
    float4 Tangent    : TANGENT0;
    float4 Binormal   : BINORMAL0;
    float4 Diffuse    : COLOR0;
    float2 TexCoord   : TEXCOORD0;
};


struct PS_IN
{
    float4 Position      : SV_POSITION;
    float4 WorldPosition : POSITION0;
    float4 Normal        : NORMAL0;
    float4 Tangent       : TANGENT0;
    float4 Binormal      : BINORMAL0;
    float4 Diffuse       : COLOR0;
    float2 TexCoord      : TEXCOORD0;
};
