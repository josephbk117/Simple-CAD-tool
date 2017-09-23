#pragma once
#include <GLM\glm.hpp>
using namespace glm;
class VertexManipulationHelper
{
public:
	enum class ManipulationType
	{
		DISTANCE, LERP_VALUE
	};
	static void setVertexAlongLine(vec4* vertexToMove, vec3 vertex1, vec3 vertex2, float manipulationValue, ManipulationType manipulationType, bool restrictWithinEdge);
	VertexManipulationHelper();
	~VertexManipulationHelper();
};

