#pragma once

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include "meshes.hpp"
#include "Texture.hpp"
#include <sstream>
#include <fstream>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "Material.hpp"

class Mesh
{
public:
	Mesh() 
	{
		loadMeshFromBuffer(
		&emptyMeshDATA[0], &emptyMeshDATA_UVs[0], 
		&emptyMeshDATA_Normals[0], emptyTexture, 1);
	}

	Mesh(std::string pathToOBJ, GLuint _shadersID)
	{
		loadFromOBJ(pathToOBJ);
		shadersID = _shadersID;
	}

	Mesh(GLfloat* data, GLfloat* UVData, GLfloat* normalData, 
	Texture _albedo, unsigned int triCount, GLuint _shadersID) : triCount(triCount), shadersID(_shadersID)
	{
		loadMeshFromBuffer(data, UVData, normalData, _albedo, triCount);
	}

	void loadMeshFromBuffer(GLfloat* data, GLfloat* UVData, GLfloat* normalData, 
	Texture _albedo, unsigned int triCount)
	{
		mat.albedo = _albedo;

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triCount * 3 * 3, data, GL_STATIC_DRAW);
	
		glGenBuffers(1, &UVBO);
		glBindBuffer(GL_ARRAY_BUFFER, UVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triCount * 3 * 3, UVData, GL_STATIC_DRAW);
		
		glGenBuffers(1, &NBO);
		glBindBuffer(GL_ARRAY_BUFFER, NBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triCount * 3 * 3, normalData, GL_STATIC_DRAW);
	}

	bool loadFromOBJ(std::string pathToOBJ)
	{
		std::cout << "Loading \"" << pathToOBJ << "\"" << std::endl;
		std::ifstream f(pathToOBJ);
		if (!f)
		{
			std::cout << "Couldn't load \"" << pathToOBJ << "\"" << std::endl;
			return false;
		}

		std::string line;
		std::string kw;

		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> UVs;
		std::vector<glm::vec3> normals;

		std::vector<glm::vec3> faces;
		std::vector<glm::vec3> facesNormals;
		std::vector<glm::vec2> facesUV;

		while (std::getline(f, line))
		{
			std::stringstream ss(line);
			
			ss >> kw;

			if (kw == "v")
			{
				glm::vec3 v;
				ss >> v.x >> v.y >> v.z;
				vertices.push_back(v);
			}
			else if (kw == "vn")
			{
				glm::vec3 n;
				ss >> n.x >> n.y >> n.z;
				normals.push_back(n);
			}
			else if (kw == "vt")
			{
				glm::vec2 t;
				ss >> t.x >> t.y;
				t.y = 1 - t.y;
				UVs.push_back(t);
			}
			else if (kw == "f")
			{
				std::string indexA_str, indexB_str, indexC_str;
				unsigned int indexA, indexB, indexC;
				std::string stra, strb, strc;

				ss >> stra >> strb >> strc;

				std::stringstream va(stra), vb(strb), vc(strc);

				std::getline(va, indexA_str, '/');
				std::getline(vb, indexB_str, '/');
				std::getline(vc, indexC_str, '/');

				indexA = std::atoi(indexA_str.c_str());
				indexB = std::atoi(indexB_str.c_str());
				indexC = std::atoi(indexC_str.c_str());

				faces.push_back(vertices[indexA - 1]);
				faces.push_back(vertices[indexB - 1]);
				faces.push_back(vertices[indexC - 1]);

				////////////////////////////////////////////////////////////////////////	

				std::getline(va, indexA_str, '/');
				std::getline(vb, indexB_str, '/');
				std::getline(vc, indexC_str, '/');

				indexA = std::atoi(indexA_str.c_str());
				indexB = std::atoi(indexB_str.c_str());
				indexC = std::atoi(indexC_str.c_str());

				facesUV.push_back(UVs[indexA - 1]);
				facesUV.push_back(UVs[indexB - 1]);
				facesUV.push_back(UVs[indexC - 1]);

				////////////////////////////////////////////////////////////////////////

				std::getline(va, indexA_str, '/');
				std::getline(vb, indexB_str, '/');
				std::getline(vc, indexC_str, '/');

				indexA = std::atoi(indexA_str.c_str());
				indexB = std::atoi(indexB_str.c_str());
				indexC = std::atoi(indexC_str.c_str());

				facesNormals.push_back(normals[indexA - 1]);
				facesNormals.push_back(normals[indexB - 1]);
				facesNormals.push_back(normals[indexC - 1]);
			}
		}

		triCount = (unsigned int)faces.size() / 3;

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triCount * 3 * 3, &faces[0], GL_STATIC_DRAW);

		glGenBuffers(1, &NBO);
		glBindBuffer(GL_ARRAY_BUFFER, NBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triCount * 3 * 3, &facesNormals[0], GL_STATIC_DRAW);

		glGenBuffers(1, &UVBO);
		glBindBuffer(GL_ARRAY_BUFFER, UVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* triCount * 3 * 3, &facesUV[0], GL_STATIC_DRAW);

		mat.albedo = Texture("resources/Meshes/Chess/rookAlbedo.png", GL_SRGB);
		mat.roughness = Texture("resources/Meshes/Chess/rookRoughness.png", GL_RGB);
		mat.metallic = true;
		mat.IOR = 1.45f;
		std::cout << "Loaded " << triCount << " triangles" << std::endl;

		f.close();
		return true;
	}

public:
	GLuint VBO;
	GLuint UVBO;
	GLuint NBO;
	unsigned int triCount;

	GLuint shadersID;

	Material mat;
};