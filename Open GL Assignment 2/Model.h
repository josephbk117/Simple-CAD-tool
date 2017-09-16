#pragma once
#include <vector>
#include <iostream>
#include <GL\glew.h>
#include <GLM\glm.hpp>
using namespace glm;

class Model
{
public:
	Model();
	~Model();
	void addVertex(vec3 vertexPosition);
	void addVertex(float x, float y, float z);
	void display();
	void updateMeshData();
	vec3* vertexAtViewportCoord(float x, float y, float z);
private:
	unsigned int VBO, VAO;
	std::vector<vec3> vertexData;

};

