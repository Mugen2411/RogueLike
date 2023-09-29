#include "BasicShaderHeader.hlsli"

float4 BasicPS(Output input) : SV_TARGET
{
	float4 col = tex.Sample(smp, input.uv);
	if(col.w == 0.0f) discard;
	return col;
}