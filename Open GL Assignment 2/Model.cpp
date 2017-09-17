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
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * 3 * sizeof(float), vertexData.data(), GL_DYNAMIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::removeVertex(vec3* vertex, Model* model)
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
/*
Can pass argument as NULL , to ignore that axis
*/
vec3 * Model::vertexAtViewportCoord(float x, float y, float z)
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

void Model::addVertex(vec3 vertexPosition)
{
	vertexData.push_back(vertexPosition);
}

void Model::addVertex(float x, float y, float z)
{
	vertexData.push_back(vec3(x, y, z));
}

void Model::display()
{
	glPointSize(5);
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, vertexData.size());
	glDrawArrays(GL_LINE_STRIP, 0, vertexData.size());
	glBindVertexArray(0);
}
