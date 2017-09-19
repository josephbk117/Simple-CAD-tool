#pragma once
#include <vector>
#include <iostream>
#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
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
	void removeVertex(vec4* vertex, Model* model);
	void setVerticesAsSelected(int* indices, unsigned int length);
	void setVerticesAsSelected(const std::vector<unsigned int> indices);
	int getIndexOfVertex(vec4 *vertex);
	vec4* vertexAtViewportCoord(float x, float y, float z);
	void translate(const vec3 &translateVector);
	mat4 getTransform();
	bool containsVertexData();
private:
	unsigned int VBO, VAO;
	std::vector<vec4> vertexData;
	mat4 transform;
};

