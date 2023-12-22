#include "Object.hpp"

void Object::updateMatrix()
{
	matrix = glm::rotate(glm::mat4(1), rotation.x, glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, -rotation.y, glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, rotation.z, glm::vec3(0, 0, 1));

	matrix = glm::scale(matrix, scale);

	matrix = glm::translate(matrix, position);
}