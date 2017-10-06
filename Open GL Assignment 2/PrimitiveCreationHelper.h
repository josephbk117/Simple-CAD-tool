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
			break;
		case PrimitiveType::SPHERE:
			return createSphere();
			break;
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
		/*
		x = x0 + rcosO + sinY
		y = y0 + rsinO + sinY
		z = z0 + rcosY

		0 <= O <= 2PI
		0 <= Y <= PI
		*/
		Model* sphere = new Model;
		const float RADIUS = 30.0f;
		const float OMEGA_INC = pi<float>() / 10.0f;
		const float THETA_INC = (2.0f*pi<float>()) / 10.0f;

		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				float X = 0, Y = 0, Z = 0;
				X = (RADIUS * cos(i * THETA_INC)) + sin(j * OMEGA_INC);
				Y = (RADIUS * sin(i * THETA_INC)) + sin(j * OMEGA_INC);
				Z = RADIUS * cos(j * OMEGA_INC);
				sphere->addVertex(X, Y, Z);
			}
		}
		sphere->updateMeshData();
		return sphere;
	}
};

