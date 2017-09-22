#include "Model.h"

Model::Model()
{
	transform = glm::mat4(1);
	addVertexFlowSplitIndex(0);
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
			/*std::cout << "\nMouse Data : " << x << " ," << y;
			vec4 transformedVertex = glm::inverse(transform) * vec4(x, y, 0, 1);
			std::cout << "\nTransformed mouse Data : " << transformedVertex.x << " ," << transformedVertex.y;*/
			//x = transformedVertex.x;
			//y = transformedVertex.y;
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

void Model::addVertex(const vec3 &vertexPosition)
{
	addVertex(vertexPosition.x, vertexPosition.y, vertexPosition.z);
}

void Model::addVertex(const vec3 & vertexPosition, unsigned int indexToPlaceVertex)
{
	vertexData.insert(vertexData.begin() + indexToPlaceVertex, vec4(vertexPosition, 0.0));
}

void Model::addVertex(float x, float y, float z)
{
	vertexData.push_back(vec4(x, y, z, 0.0));
}

void Model::display(bool showVertices, ShaderProgram *shader)
{
	glPointSize(5);
	shader->use();
	shader->setMat4("model", transform);
	std::vector<GLint> first(vertexSections.size());
	std::vector<GLsizei> count(vertexSections.size());
	vertexSections[vertexSections.size() - 1].count = 
		vertexData.size() - vertexSections[vertexSections.size() - 1].first;
	for (int i = 0; i < vertexSections.size(); i++)
	{
		first[i] = vertexSections[i].first;
		count[i] = vertexSections[i].count;
	}
	glBindVertexArray(VAO);
	if (showVertices)
		glMultiDrawArrays(GL_POINTS, first.data(), count.data(), vertexSections.size());
	glMultiDrawArrays(GL_LINE_STRIP, first.data(), count.data(), vertexSections.size());
	glBindVertexArray(0);
}

void Model::addVertexFlowSplitIndex(unsigned int index)
{
	vertexSections.push_back(VertexSection(index, vertexData.size() - index));
}
