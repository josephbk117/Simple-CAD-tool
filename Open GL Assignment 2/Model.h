#pragma once
#include <vector>
#include <iostream>
#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

class Model
{
public:
	Model();
	~Model();
	void addVertex(const vec3 &vertexPosition);
	void addVertex(float x, float y, float z);
	void display(bool showVertices);
	void updateMeshData();
	void removeVertex(vec3* vertex, Model* model);
	vec3* vertexAtViewportCoord(float x, float y, float z);
	void translate(const vec3 &translateVector);
	bool containsVertexData();
private:
	unsigned int VBO, VAO;
	std::vector<vec3> vertexData;
	mat4 transform;
};

