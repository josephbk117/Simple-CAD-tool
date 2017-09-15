#pragma once
#include <vector>
#include <iostream>
#include <GL\glew.h>
#include <GLM\glm.hpp>
class Model
{
public:
	Model();
	~Model();
	void addVertex(glm::vec3 vertexPosition);
	void addVertex(float x, float y, float z);
	void display();
	void updateMeshData();
private:
	unsigned int VBO, VAO;
	std::vector<float> vertexData;

};

