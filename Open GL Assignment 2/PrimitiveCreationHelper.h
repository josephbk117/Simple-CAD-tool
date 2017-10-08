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

		cube->addVertexWithNoIndexData(SIZE, SIZE, SIZE);//0
		cube->addVertexWithNoIndexData(-SIZE, SIZE, SIZE);//1
		cube->addVertexWithNoIndexData(-SIZE, -SIZE, SIZE);//2
		cube->addVertexWithNoIndexData(SIZE, -SIZE, SIZE);//3

		cube->addVertexWithNoIndexData(SIZE, SIZE, -SIZE);//4
		cube->addVertexWithNoIndexData(-SIZE, SIZE, -SIZE);//5
		cube->addVertexWithNoIndexData(-SIZE, -SIZE, -SIZE);//6
		cube->addVertexWithNoIndexData(SIZE, -SIZE, -SIZE);//7
		//____SQUARE 1___
		cube->addVertexFlowSplitIndex(0);
		cube->addVertexFlowSplitIndex(1);

		cube->addVertexFlowSplitIndex(1);
		cube->addVertexFlowSplitIndex(2);

		cube->addVertexFlowSplitIndex(2);
		cube->addVertexFlowSplitIndex(3);

		cube->addVertexFlowSplitIndex(3);
		cube->addVertexFlowSplitIndex(0);

		//___SQUARE 2___
		cube->addVertexFlowSplitIndex(4);
		cube->addVertexFlowSplitIndex(5);

		cube->addVertexFlowSplitIndex(5);
		cube->addVertexFlowSplitIndex(6);

		cube->addVertexFlowSplitIndex(6);
		cube->addVertexFlowSplitIndex(7);

		cube->addVertexFlowSplitIndex(7);
		cube->addVertexFlowSplitIndex(4);
		//___CONNECTING LINE___
		cube->addVertexFlowSplitIndex(0);
		cube->addVertexFlowSplitIndex(4);

		cube->addVertexFlowSplitIndex(1);
		cube->addVertexFlowSplitIndex(5);

		cube->addVertexFlowSplitIndex(2);
		cube->addVertexFlowSplitIndex(6);

		cube->addVertexFlowSplitIndex(3);
		cube->addVertexFlowSplitIndex(7);

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
			cone->addVertexFlowSplitIndex(j);
			cone->addVertexFlowSplitIndex((j + 1) % COUNT);
			cone->addVertexFlowSplitIndex(j);
			cone->addVertexFlowSplitIndex(10);

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
			cylinder->addVertexFlowSplitIndex(j);
			cylinder->addVertexFlowSplitIndex((j + 1) % COUNT);
			cylinder->addVertexFlowSplitIndex(j);
			cylinder->addVertexFlowSplitIndex(j + COUNT);
		}

		for (int j = 0; j < COUNT; j++)
		{
			float x = RADIUS * sin(j * THETA_INC);
			float z = RADIUS * cos(j * THETA_INC);
			cylinder->addVertexWithNoIndexData(x, RADIUS, z);
			cylinder->addVertexFlowSplitIndex(j + COUNT);
			cylinder->addVertexFlowSplitIndex(((j + 1) % COUNT) + COUNT);
		}

		cylinder->updateMeshData();
		return cylinder;
	}
};

