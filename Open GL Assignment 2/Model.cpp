#include "Model.h"

Model::Model()
{
	transform = glm::mat4(1);
	addVertexFlowSplitIndex(0);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

Model::~Model()
{
}

void Model::updateMeshData()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * 4 * sizeof(float), vertexData.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	unsigned int dataCount = 0;
	std::cout << "\n____________";
	for (int i = 0; i < vertexSections.size(); i++)
	{
		dataCount += vertexSections[i].size();
		std::cout << "\n-------::::-------";
		for (int j = 0; j < vertexSections[i].size(); j++)
		{
			std::cout << "\nData : " << i << " " << j << " = " << vertexSections[i][j];
		}
	}

	/*if (vertexData.size() > 1)
	{
		unsigned int indices[14] = {
			0,1,
			1,2,
			2,3,
			2,4,
			2,5,
			2,6,
			2,7
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 14 * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW);
	}
	else*/
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataCount * sizeof(unsigned int), &vertexSections[0][0], GL_DYNAMIC_DRAW);
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
	//vertexData.insert(vertexData.begin() + indexToPlaceVertex, vec4(vertexPosition, 0.0));
	//vertexIndices.push_back(indexToPlaceVertex);
	//addVertex(vertexPosition.x, vertexPosition.y, vertexPosition.z);
	vertexData.push_back(vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 0.0));
	vertexSections[vertexSections.size() - 1].push_back(indexToPlaceVertex);
	vertexSections[vertexSections.size() - 1].push_back(vertexData.size());
}

void Model::addVertex(float x, float y, float z)
{
	vertexData.push_back(vec4(x, y, z, 0.0));
	vertexIndices.push_back(vertexIndices.size());
	vertexSections[vertexSections.size() - 1].push_back(vertexData.size());
}

void Model::display(bool showVertices, ShaderProgram *shader)
{
	glPointSize(5);
	shader->use();
	shader->setMat4("model", transform);

	unsigned int numberOfData = 0;
	for (int i = 0; i < vertexSections.size(); i++)
	{
		numberOfData += vertexSections[i].size();
	}

	glBindVertexArray(VAO);

	glDrawElements(GL_LINE_STRIP, numberOfData - 1, GL_UNSIGNED_INT, 0);
	if (showVertices)
		glDrawElements(GL_POINTS, numberOfData - 1, GL_UNSIGNED_INT, 0);


	glBindVertexArray(0);
}

void Model::addVertexFlowSplitIndex(unsigned int index)
{
	std::vector<unsigned int> newData;
	newData.push_back(index);
	vertexSections.push_back(newData);
}
