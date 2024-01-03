#pragma once

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <glm/vec3.hpp>

class Texture
{
public:
	Texture(std::string path, GLint colorSpace = GL_SRGB);
	Texture(unsigned int width = 1, unsigned int height = 1, glm::vec3 color = glm::vec3(0), GLint colorSpace = GL_SRGB);
	void bind(GLenum textureUnit = GL_TEXTURE0);
	void loadFromFile(std::string path, GLint colorSpace = GL_SRGB);

public:
	unsigned int texture;
};

namespace
{
	Texture emptyTexture("resources/Images/black.png");
}