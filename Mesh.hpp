#pragma once

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include "meshes.hpp"

class Mesh
{
public:
	Mesh() 
	{
		loadMeshFromBuffer(&emptyMesh[0], 1);
	}

	Mesh(GLfloat* data, unsigned int triCount) : triCount(triCount)
	{
		loadMeshFromBuffer(data, triCount);
	}

	void loadMeshFromBuffer(GLfloat* data, unsigned int triCount)
	{
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triCount * 3 * 3, data, GL_STATIC_DRAW);
	}

public:
	GLuint VBO;
	unsigned int triCount;
};