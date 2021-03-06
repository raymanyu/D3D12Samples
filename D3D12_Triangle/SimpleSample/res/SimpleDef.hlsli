//-------------------------------------------------------------------------------------------------
// File : SimpleDef.hlsli
// Desc : Data Layout.
// Copyright(c) Project Asura. All right reserved.
//-------------------------------------------------------------------------------------------------


///////////////////////////////////////////////////////////////////////////////////////////////////
// VSInput structure
///////////////////////////////////////////////////////////////////////////////////////////////////
struct VSInput
{
    float3  Position : POSITION;
    float3  Normal   : NORMAL;
    float2  TexCoord : TEXCOORD;
    float4  Color    : VTX_COLOR;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// VSOutput structure
///////////////////////////////////////////////////////////////////////////////////////////////////
struct VSOutput
{
    float4  Position : SV_POSITION;
    float3  Normal   : NORMAL;
    float2  TexCoord : TEXCOORD;
    float4  Color    : VTX_COLOR;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// PSOutput structure
///////////////////////////////////////////////////////////////////////////////////////////////////
struct PSOutput
{
    float4  Color   : SV_TARGET0;
};


///////////////////////////////////////////////////////////////////////////////////////////////////
// TransformBuffer constant buffer
///////////////////////////////////////////////////////////////////////////////////////////////////
cbuffer TransformBuffer : register(b0)
{
    float4x4 World : packoffset(c0);
    float4x4 View  : packoffset(c4);
    float4x4 Proj  : packoffset(c8);
};

