#pragma once

#include "Texture.hpp"

class Material
{
public:
	Material(
	Texture albedo = emptyTexture, Texture roughness = Texture(1, 1, glm::vec3(0.5f), GL_RGB), 
	bool metallic = false, float IOR = 1.45f, Texture normalMap = Texture(1, 1, glm::vec3(0.5f, 0.5f, 1.f), 
	GL_RGB)) :
	albedo(albedo), roughness(roughness), metallic(metallic), IOR(IOR)
	{ }
public:
	Texture albedo;
	Texture roughness;
	Texture normalMap;
	bool metallic;
	float IOR;
};