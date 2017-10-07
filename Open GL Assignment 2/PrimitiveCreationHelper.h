#pragma once
#include <iostream>
#include <GLM\glm.hpp>
#include "Model.h"

enum class PrimitiveType
{
	CUBE, SPHERE, CYLINDER, CONE
};
class PrimitiveCreationHelper
{
public:
	static Model* createPrimitive(PrimitiveType primitive)
	{
		switch (primitive)
		{
		case PrimitiveType::CUBE:
			return createCube();
		case PrimitiveType::SPHERE:
			return createSphere();
		case PrimitiveType::CYLINDER:
			break;
		case PrimitiveType::CONE:
			break;
		default:
			break;
		}
	}
private:
	static Model* createSphere()
	{
		Model* sphere = new Model;
		int const COUNT = 10;
		float const THETA_INC = 2 * pi<float>() / (float)COUNT;
		float const OMEGA_INC = pi<float>() / (float)COUNT;
		float const RADIUS = 60.0f;

		for (int i = 0; i <= COUNT; i++)
		{
			for (int j = 0; j <= COUNT; j++)
			{
				float x = RADIUS * sin(j * THETA_INC) * sin(i * OMEGA_INC);
				float y = RADIUS * cos(j * THETA_INC) * sin(i * OMEGA_INC);
				float z = RADIUS * cos(i * OMEGA_INC);
				sphere->addVertex(x, y, z);
			}
		}
		sphere->updateMeshData();
		return sphere;
	}
	static Model* createCube()
	{
		Model* cube = new Model;
		const float SIZE = 60.0f;

		cube->addVertex(SIZE, SIZE, SIZE);
		cube->addVertex(-SIZE, SIZE, SIZE);
		cube->addVertex(-SIZE, -SIZE, SIZE);
		cube->addVertex(SIZE, -SIZE, SIZE);

		cube->addVertex(SIZE, SIZE, -SIZE);
		cube->addVertex(-SIZE, SIZE, -SIZE);
		cube->addVertex(-SIZE, -SIZE, -SIZE);
		cube->addVertex(SIZE, -SIZE, -SIZE);

		cube->updateMeshData();
		return cube;
	}
};

