struct Output
{
	float4 svpos : SV_POSITION;
	float2 uv : TEXCOORD;
};
Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);
cbuffer cbuff0 : register(b0)
{
	matrix move;
	matrix rot;
	matrix scale;
	float4 brightness;
    float4 dummy1;
    float4 dummy2;
    float4 dummy3;
}