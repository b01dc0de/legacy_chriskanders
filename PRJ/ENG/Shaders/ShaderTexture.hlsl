#pragma pack_matrix(row_major)

Texture2D main_texture : register(t0);

SamplerState main_sampler : register(s0);

cbuffer ViewProjBuffer : register(b0)
{
    float4x4 view;
    float4x4 proj;
}

cbuffer WorldBuffer : register(b1)
{
    float4x4 world;
}

struct VS_INPUT
{
    float4 pos : POSITION;
    float2 tex : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

VS_OUTPUT VSMain(VS_INPUT input)
{
    VS_OUTPUT output;

    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    output.tex = input.tex;

    return output;
}

float4 PSMain(VS_OUTPUT input) : SV_Target
{
    return main_texture.Sample(main_sampler, input.tex);
}