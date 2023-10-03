//
//struct PixelShaderOutput {
//	float32_t4 color : SV_TARGET0;
//};
//
//PixelShaderOutput main() {
//	PixelShaderOutput output;
//	output.color = float32_t4(1.0, 1.0, 1.0, 1.0);
//	return output;
//}

#include "Object3d.hlsli"

struct Material {
	float32_t4 color;
};
ConstantBuffer<Material> gMaterial : register(b0);

Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);

struct PixelShaderOutput {
	float32_t4 color : SV_TARGET0;
};
PixelShaderOutput main(VertexShaderOutput input) {
	PixelShaderOutput output;
	float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);
	output.color = gMaterial.color * textureColor;
	return output;
}