#pragma once

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <iostream>

class Texture
{
public:
	Texture(std::string path = "", GLint colorSpace = GL_SRGB);
	void bind(GLenum textureUnit = GL_TEXTURE0);
	void loadFromFile(std::string path, GLint colorSpace = GL_SRGB);

public:
	unsigned int texture;
};

namespace
{
	Texture emptyTexture("resources/Images/black.png");
}