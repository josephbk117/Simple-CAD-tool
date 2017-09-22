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
	void display(bool showVertices, ShaderProgram *shader);
	void addVertexFlowSplitIndex(unsigned int index);
	void updateMeshData();
	void removeVertex(vec4* vertex, Model* model);
	void setVerticesAsSelected(int* indices, unsigned int length);
	void setVerticesAsSelected(const std::vector<unsigned int> indices);
	void clearSelectedVertcies();
	int getIndexOfVertex(vec4 *vertex);
	vec4* vertexAtViewportCoord(float x, float y, float z);
	vec4* vertexAtIndex(unsigned int index);
	void translate(const vec3 &translateVector);
	void setTransform(const mat4 &transformMaipulation);
	mat4 getTransform();
	bool containsVertexData();
private:
	unsigned int VBO, VAO;
	std::vector<vec4> vertexData;
	std::vector<VertexSection> vertexSections;
	mat4 transform;
};

