#include "BasicShaderHeader.hlsli"

Output BasicVS(float4 pos : POSITION, float2 uv : TEXCOORD)
{
	Output output;
	output.svpos = mul(rot, pos);
	output.svpos = mul(scale, output.svpos);
	output.svpos = mul(move, output.svpos);
	output.uv = uv;
	return output;
}