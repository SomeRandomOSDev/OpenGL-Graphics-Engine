#pragma once

#include "Mesh.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Object
{
public:
	Object() : mesh(), position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1) {}

public:
	Mesh mesh;
	glm::vec3 position, rotation, scale;
};