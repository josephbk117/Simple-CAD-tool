#include "Model.h"
/*
	Allow user to create new vertices from the specified vertex

*/
Model::Model()
{
	transform = glm::mat4(1);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

Model::~Model()
{
}

void Model::display(bool showVertices, ShaderProgram *shader)
{
	glPointSize(5);
	shader->use();
	shader->setMat4("model", transform);
	glBindVertexArray(VAO);

	glDrawElements(GL_LINES, vertexSections.size(), GL_UNSIGNED_INT, 0);
	if (showVertices)
		glDrawElements(GL_POINTS, vertexSections.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Model::updateMeshData()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * 4 * sizeof(float), vertexData.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	std::cout << "\n____________";
	for (int i = 0; i < vertexSections.size(); i++)
	{
		std::cout << "\nVetex Sections at " << i << " = " << vertexSections[i];
	}
	if (vertexSections.size() > 0)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexSections.size() * sizeof(unsigned int), vertexSections.data(), GL_DYNAMIC_DRAW);
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
	if (length <= 0)
	{
		for (int i = 0; i < length; i++)
			vertexData[i].w = 0.0f;
	}
	for (int i = 0; i < length; i++)
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
	if (indices.size() <= 0)
	{
		for (int i = 0; i < vertexData.size(); i++)
			vertexData[i].w = 0.0f;
	}
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
void Model::setVerticesAsSelected(std::vector<vec4 *> vertices)
{
	if (vertices.size() <= 0)
	{
		for (int i = 0; i < vertexData.size(); i++)
			vertexData[i].w = 0.0f;
	}
	for (int i = 0; i < vertexData.size(); i++)
	{
		for (int j = 0; j < vertices.size(); j++)
		{
			if (&vertexData[i] == vertices[j])
			{
				vertexData[i].w = 1.0f;
				break;
			}
			else
				vertexData[i].w = 0.0f;
		}
	}
}
void Model::clearSelectedVertcies()
{
	for (int i = 0; i < vertexData.size(); i++)
		vertexData[i].w = 0.0f;
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

vec4* Model::vertexAtIndex(unsigned int index)
{
	return &vertexData[index];
}

void Model::translate(const vec3 &translateVector)
{
	transform = glm::translate(transform, translateVector);
}

void Model::setTransform(const mat4 &transformMaipulation)
{
	transform = transformMaipulation;
}

mat4 Model::getTransform()
{
	return transform;
}

bool Model::containsVertexData()
{
	return (vertexData.size() > 0) ? true : false;
}

unsigned int Model::getVertexCount()
{
	return vertexData.size();
}

void Model::addVertex(const vec3 &vertexPosition)
{
	addVertex(vertexPosition.x, vertexPosition.y, vertexPosition.z);
}

void Model::addVertex(const vec3 & vertexPosition, unsigned int indexToPlaceVertex)
{
	vertexData.push_back(vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 0.0));
	vertexSections.push_back(indexToPlaceVertex);
	vertexSections.push_back(vertexData.size() - 1);
}

void Model::addVertex(float x, float y, float z)
{
	vertexData.push_back(vec4(x, y, z, 0.0));
	if (vertexSections.size() < 2)
		vertexSections.push_back(vertexSections.size());
	else
	{
		unsigned int lastIndexValue = vertexSections[vertexSections.size() - 1];
		vertexSections.push_back(lastIndexValue);
		vertexSections.push_back(lastIndexValue + 1);
	}
}

void Model::addVertexFlowSplitIndex(unsigned int index)
{
	vertexSections.push_back(index);
}
