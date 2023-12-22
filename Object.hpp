#pragma once

#include "Mesh.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Object
{
public:
	Object() : mesh(), position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1), matrix(1) {}
	Object(Mesh mesh = Mesh(), glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 rotation = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1, 1, 1)) :
	mesh(mesh), position(position), rotation(rotation), scale(scale), matrix(1)
	{
		updateMatrix();
	}

	void updateMatrix();

public:
	Mesh mesh;
	glm::vec3 position, rotation, scale;
	glm::mat4 matrix;
};