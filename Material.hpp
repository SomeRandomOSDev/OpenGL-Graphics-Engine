#pragma once

#include "Texture.hpp"

class Material
{
public:
	Material(Texture albedo = emptyTexture, float roughness = 0.8f, bool metallic = false, float IOR = 1.45f) :
	albedo(albedo), roughness(roughness), metallic(metallic), IOR(IOR)
	{ }
public:
	Texture albedo;
	float roughness;
	bool metallic;
	float IOR;
};