#pragma once
#include <vector>
#include <iostream>
#include <GL\glew.h>
#include <GLM\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "ShaderProgram.h"
using namespace glm;

class Model
{
public:
	Model();
	~Model();
	void addVertex(const vec3 &vertexPosition);
	void addVertex(float x, float y, float z);
	void display(bool showVertices, ShaderProgram *shader);
	void addVertexFlowSplitIndex(unsigned int index);
	void updateMeshData();
	void removeVertex(vec4* vertex, Model* model);
	void setVerticesAsSelected(int* indices, unsigned int length);
	void setVerticesAsSelected(const std::vector<unsigned int> indices);
	void clearSelectedVertcies();
	int getIndexOfVertex(vec4 *vertex);
	vec4* vertexAtViewportCoord(float x, float y, float z);
	void translate(const vec3 &translateVector);
	void setTransform(const mat4 &transformMaipulation);
	bool containsVertexData();
private:
	unsigned int VBO, VAO;
	std::vector<vec4> vertexData;
	std::vector<unsigned int> seperationIndices;
	mat4 transform;
};

