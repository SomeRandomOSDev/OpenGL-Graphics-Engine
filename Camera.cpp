#include "Camera.hpp"

void Camera::updateMatrices()
{
	projectionMatrix = glm::perspective(
		glm::radians(FOV), aspectRatio, zNear, zFar);

	viewMatrix = glm::rotate(glm::mat4(1), -rotation.x, glm::vec3(1, 0, 0));
	viewMatrix = glm::rotate(viewMatrix, rotation.y, glm::vec3(0, 1, 0));
	viewMatrix = glm::rotate(viewMatrix, -rotation.z, glm::vec3(0, 0, 1));

	viewMatrix = glm::translate(viewMatrix, -position);
}

void Camera::handleFreeCam(float deltaTime, float rotationSpeed, float movementSpeed)
{
	sf::Vector2f mouseDelta = (sf::Vector2f)(sf::Mouse::getPosition() - screenCenter);

	rotation.y += deltaTime * mouseDelta.x * rotationSpeed;
	rotation.x -= deltaTime * mouseDelta.y * rotationSpeed;

	glm::vec3 movementVector(0, 0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		movementVector.z += -cos(-rotation.y);
		movementVector.x += -sin(-rotation.y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movementVector.z += cos(-rotation.y);
		movementVector.x += sin(-rotation.y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		movementVector.z += -cos(-rotation.y + PI / 2);
		movementVector.x += -sin(-rotation.y + PI / 2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movementVector.z += cos(-rotation.y + PI / 2);
		movementVector.x += sin(-rotation.y + PI / 2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		movementVector.y += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movementVector.y -= 1;
	}

	if(movementVector != glm::vec3(0, 0, 0))
		movementVector = normalize(movementVector);

	movementVector *= movementSpeed * deltaTime;

	position += movementVector;

	updateMatrices();

	sf::Mouse::setPosition(screenCenter);
}