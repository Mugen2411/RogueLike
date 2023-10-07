#include "BasicShaderHeader.hlsli"

float4 BasicPS(Output input) : SV_TARGET
{
	float4 col = tex.Sample(smp, input.uv) * brightness;
	//float4 col = float4(1.0f, 0.0f, 0.0f, 1.0f);
	if(col.w == 0.0f) discard;
	return col;
}