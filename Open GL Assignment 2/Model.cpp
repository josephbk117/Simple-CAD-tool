#include "Model.h"

Model::Model()
{
	transform = glm::mat4(1);
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
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * 4 * sizeof(float), vertexData.data(), GL_DYNAMIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//selection index thing attribute
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::removeVertex(vec4* vertex, Model* model)
{
	std::cout << "\nVertex count = " << vertexData.size();
	for (int i = 0; i < vertexData.size(); i++)
	{
		if (vertex == &vertexData[i])
		{
			vertexData.erase(vertexData.begin() + i);
			break;
		}
	}
}
void Model::setVerticesAsSelected(int* indices, unsigned int length)
{
	for (int i = 0; i < vertexData.size(); i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (i == indices[j])
			{
				vertexData[i].w = 1.0f;
				break;
			}
			else
				vertexData[i].w = 0.0f;
		}
	}
}

void Model::setVerticesAsSelected(const std::vector<unsigned int> indices)
{
	for (int i = 0; i < vertexData.size(); i++)
	{
		for (int j = 0; j < indices.size(); j++)
		{
			if (i == indices[j])
			{
				vertexData[i].w = 1.0f;
				break;
			}
			else
				vertexData[i].w = 0.0f;
		}
	}
}

int Model::getIndexOfVertex(vec4 *vertex)
{
	for (int i = 0; i < vertexData.size(); i++)
	{
		if (vertex == &vertexData[i])
			return i;
	}
}

vec4 * Model::vertexAtViewportCoord(float x, float y, float z)
{
	for (int i = 0; i < vertexData.size(); i++)
	{
		if (x == NULL)
		{
			if (vertexData[i].y > y - 10 && vertexData[i].y < y + 10)
			{
				if (vertexData[i].z > z - 10 && vertexData[i].z < z + 10)
				{
					return &vertexData[i];
					break;
				}
			}
		}
		else if (y == NULL)
		{
			if (vertexData[i].x > x - 10 && vertexData[i].x < x + 10)
			{
				if (vertexData[i].z > z - 10 && vertexData[i].z < z + 10)
				{
					return &vertexData[i];
					break;
				}
			}
		}
		else if (z == NULL)
		{
			if (vertexData[i].x > x - 10 && vertexData[i].x < x + 10)
			{
				if (vertexData[i].y > y - 10 && vertexData[i].y < y + 10)
				{
					return &vertexData[i];
					break;
				}
			}
		}
	}
	return nullptr;
}

void Model::translate(const vec3 &translateVector)
{
	transform = glm::translate(transform, translateVector);
}

mat4 Model::getTransform()
{
	return transform;
}

bool Model::containsVertexData()
{
	return (vertexData.size() > 0) ? true : false;
}

void Model::addVertex(const vec3 &vertexPosition)
{
	vertexData.push_back(vec4(vertexPosition, 0.0));
}

void Model::addVertex(float x, float y, float z)
{
	vertexData.push_back(vec4(x, y, z, 0.0));
}

void Model::display(bool showVertices)
{
	glPointSize(5);
	if (seperationIndices.size() > 0)
	{
		glEnable(GL_PRIMITIVE_RESTART);
		for (int i = 0; i < seperationIndices.size(); i++)
			glPrimitiveRestartIndex(seperationIndices[i]);
	}

	glBindVertexArray(VAO);
	if (showVertices)
		glDrawArrays(GL_POINTS, 0, vertexData.size());
	glDrawArrays(GL_LINE_STRIP, 0, vertexData.size());
	glBindVertexArray(0);
	glDisable(GL_PRIMITIVE_RESTART);
}

void Model::addVertexFlowSplit(unsigned int index)
{
	seperationIndices.push_back(index);
}
