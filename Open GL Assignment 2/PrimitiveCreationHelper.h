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
			return createCylinder();
		case PrimitiveType::CONE:
			return createCone();
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
		int numberIters = 0;
		for (int i = 0; i <= COUNT; i++)
		{
			for (int j = 0; j <= COUNT; j++)
			{
				float x = RADIUS * sin(j * THETA_INC) * sin(i * OMEGA_INC);
				float y = RADIUS * cos(j * THETA_INC) * sin(i * OMEGA_INC);
				float z = RADIUS * cos(i * OMEGA_INC);
				sphere->addVertexWithNoIndexData(x, y, z);
				sphere->addVertexFlowSplitPair(numberIters, min(numberIters + 1,110));
				sphere->addVertexFlowSplitPair(numberIters, max(numberIters - (COUNT+1), 0));
				numberIters++;
			}
		}
		sphere->updateMeshData();
		return sphere;
	}
	static Model* createCube()
	{
		Model* cube = new Model;
		const float SIZE = 60.0f;

		cube->addVertexWithNoIndexData(SIZE, SIZE, SIZE);
		cube->addVertexWithNoIndexData(-SIZE, SIZE, SIZE);
		cube->addVertexWithNoIndexData(-SIZE, -SIZE, SIZE);
		cube->addVertexWithNoIndexData(SIZE, -SIZE, SIZE);

		cube->addVertexWithNoIndexData(SIZE, SIZE, -SIZE);
		cube->addVertexWithNoIndexData(-SIZE, SIZE, -SIZE);
		cube->addVertexWithNoIndexData(-SIZE, -SIZE, -SIZE);
		cube->addVertexWithNoIndexData(SIZE, -SIZE, -SIZE);

		cube->addVertexFlowSplitPair(0, 1);
		cube->addVertexFlowSplitPair(1, 2);
		cube->addVertexFlowSplitPair(2, 3);
		cube->addVertexFlowSplitPair(3, 0);

		cube->addVertexFlowSplitPair(4, 5);
		cube->addVertexFlowSplitPair(5, 6);
		cube->addVertexFlowSplitPair(6, 7);
		cube->addVertexFlowSplitPair(7, 4);

		cube->addVertexFlowSplitPair(0, 4);
		cube->addVertexFlowSplitPair(1, 5);
		cube->addVertexFlowSplitPair(2, 6);
		cube->addVertexFlowSplitPair(3, 7);

		cube->updateMeshData();
		return cube;
	}
	static Model* createCone()
	{
		Model* cone = new Model;
		int const COUNT = 10;
		float const THETA_INC = 2 * pi<float>() / (float)COUNT;
		float const RADIUS = 60.0f;

		for (int j = 0; j < COUNT; j++)
		{
			float x = RADIUS * sin(j * THETA_INC);
			float z = RADIUS * cos(j * THETA_INC);
			cone->addVertexWithNoIndexData(x, -RADIUS / 2, z);
			cone->addVertexFlowSplitPair(j, (j + 1) % COUNT);
			cone->addVertexFlowSplitPair(j, 10);
		}
		cone->addVertexWithNoIndexData(0, RADIUS / 2, 0);
		cone->updateMeshData();
		return cone;
	}
	static Model* createCylinder()
	{
		Model* cylinder = new Model;
		int const COUNT = 10;
		float const THETA_INC = 2 * pi<float>() / (float)COUNT;
		float const RADIUS = 60.0f;

		for (int j = 0; j < COUNT; j++)
		{
			float x = RADIUS * sin(j * THETA_INC);
			float z = RADIUS * cos(j * THETA_INC);
			cylinder->addVertexWithNoIndexData(x, -RADIUS, z);
			cylinder->addVertexFlowSplitPair(j, (j + 1) % COUNT);
			cylinder->addVertexFlowSplitPair(j, j + COUNT);
		}

		for (int j = 0; j < COUNT; j++)
		{
			float x = RADIUS * sin(j * THETA_INC);
			float z = RADIUS * cos(j * THETA_INC);
			cylinder->addVertexWithNoIndexData(x, RADIUS, z);
			cylinder->addVertexFlowSplitPair(j + COUNT, ((j + 1) % COUNT) + COUNT);
		}

		cylinder->updateMeshData();
		return cylinder;
	}
};

