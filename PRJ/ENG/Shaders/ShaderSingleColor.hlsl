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

cbuffer ColorBuffer : register(b2)
{
    float4 selected_color;
}

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

VS_OUTPUT VSMain(float4 in_pos : POSITION)
{
    VS_OUTPUT output;
    
    output.pos = mul(in_pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    output.color = selected_color;

    return output;
}

float4 PSMain(VS_OUTPUT input) : SV_Target
{
    return input.color;
}