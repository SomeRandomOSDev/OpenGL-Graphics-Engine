#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "util.hpp"

class Camera
{
public:
	Camera(float FOV, float aspectRatio, glm::vec3 position, glm::vec3 rotation,
		float zNear = 0.1f, float zFar = 1000.f) : 
		FOV(FOV), aspectRatio(aspectRatio), zNear(zNear), zFar(zFar), 
		position(position), rotation(rotation)
	{ 
		updateMatrices();
	}

	void updateMatrices();
	void handleFreeCam(float deltaTime, float rotationSpeed, float movementSpeed);

public:
	glm::mat4 projectionMatrix, viewMatrix;
	glm::vec3 rotation, position;
	float aspectRatio;
	float zNear, zFar;
	float FOV;
};