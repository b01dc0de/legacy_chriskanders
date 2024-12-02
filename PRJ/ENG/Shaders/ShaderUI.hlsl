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

cbuffer ImageBuffer : register(b2)
{
    float4 img_rect;
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
    float4 img_rect : COLOR;
};

VS_OUTPUT VSMain(VS_INPUT input)
{
    VS_OUTPUT output;

    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    output.pos.w = 1.0f;
    output.tex = input.tex;
    output.img_rect = img_rect;

    return output;
}

float4 PSMain(VS_OUTPUT input) : SV_Target
{
    float x_min = input.img_rect.x;
    float x_stretch = input.img_rect.z;
    float y_min = input.img_rect.y;
    float y_stretch = input.img_rect.w;

    float2 rect_tex;
    rect_tex.x = x_min + (input.tex.x * x_stretch);
    rect_tex.y = y_min + (input.tex.y * y_stretch);
    return main_texture.Sample(main_sampler, rect_tex);
}