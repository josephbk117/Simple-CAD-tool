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
	struct VertexSection
	{
		int first;
		int count;
		VertexSection(int _first, int _count)
		{
			first = _first;
			count = _count;
		}
	};
public:
	Model();
	~Model();
	void addVertex(const vec3 &vertexPosition);
	void addVertex(const vec3 &vertexPosition, unsigned int indexToPlaceVertex);
	void addVertex(float x, float y, float z);
	void addVertexWithNoIndexData(float x, float y, float z);
	void display(bool showVertices, ShaderProgram *shader);
	void addVertexFlowSplitIndex(unsigned int index);
	void addVertexFlowSplitPair(unsigned int index1, unsigned int index2);
	void updateMeshData();
	void removeVertex(vec4* vertex, Model* model);
	void setVerticesAsSelected(int* indices, unsigned int length);
	void setVerticesAsSelected(const std::vector<unsigned int> indices);
	void setVerticesAsSelected(std::vector<vec4 *> vertex);
	void clearSelectedVertcies();
	void translate(const vec3 &translateVector);
	void setTransform(const mat4 &transformMaipulation);
	int getIndexOfVertex(vec4 *vertex);
	bool containsVertexData();
	unsigned int getVertexCount();
	vec4* vertexAtViewportCoord(float x, float y, float z);
	vec4* vertexAtIndex(unsigned int index);
	mat4 getTransform();
private:
	unsigned int VBO, VAO, EBO;
	std::vector<vec4> vertexData;
	std::vector<unsigned int> vertexSections;
	mat4 transform;
};

