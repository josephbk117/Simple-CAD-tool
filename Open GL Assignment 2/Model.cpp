#include "Model.h"

Model::Model()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
}

Model::~Model()
{
}

void Model::updateMeshData()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_DYNAMIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::addVertex(glm::vec3 vertexPosition)
{
	vertexData.push_back(vertexPosition.x);
	vertexData.push_back(vertexPosition.y);
	vertexData.push_back(vertexPosition.z);
}

void Model::addVertex(float x, float y, float z)
{
	vertexData.push_back(x);
	vertexData.push_back(y);
	vertexData.push_back(z);
}

void Model::display()
{
	glPointSize(5);
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, vertexData.size() / 3);
	glDrawArrays(GL_LINE_STRIP, 0, vertexData.size() / 3);
	glBindVertexArray(0);
}
