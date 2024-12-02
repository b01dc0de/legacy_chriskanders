#pragma pack_matrix( row_major )

cbuffer ViewProjBuffer : register(b0)
{
    matrix view;
    matrix proj;
}

cbuffer WorldBuffer : register(b1)
{
    matrix world;
}

struct VS_INPUT
{
    float4 pos : POSITION;
    float2 uv : TEXCOORD;
    float4 color : COLOR;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

VS_OUTPUT VSMain(VS_INPUT input)
{
    VS_OUTPUT output;

    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    output.color = input.color;

    return output;
}

float4 PSMain(VS_OUTPUT input) : SV_Target
{
    return input.color;
}