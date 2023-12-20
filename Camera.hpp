#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(float FOV, float aspectRatio, glm::vec3 position, glm::vec3 lookAt,
		float zNear = 0.1f, float zFar = 1000.f) : 
		projectionMatrix(glm::perspective(
		glm::radians(FOV), aspectRatio, zNear, zFar)),
		viewMatrix(glm::lookAt(position, lookAt, glm::vec3(0, 1, 0)))
	{ }

public:
	glm::mat4 projectionMatrix, viewMatrix;
};