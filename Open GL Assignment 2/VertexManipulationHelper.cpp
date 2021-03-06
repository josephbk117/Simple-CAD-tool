#include "VertexManipulationHelper.h"

void VertexManipulationHelper::setVertexAlongLine(vec4 * vertexToMove, vec3 vertex1, vec3 vertex2, float manipulationValue, ManipulationType manipulationType, bool restrictWithinEdge)
{
	vec3 lineVector = vec3(vertex2.x, vertex2.y, vertex2.z) - vec3(vertex1.x, vertex1.y, vertex1.z);
	float magnitudeDistance = glm::distance(vertex1, vertex2);
	lineVector = normalize(lineVector);
	vec3 transformedPoint; //= vertex1 + (lineVector * );
	if (manipulationType == ManipulationType::DISTANCE)
	{
		if (restrictWithinEdge)
		{
			if (manipulationValue < 0)
				manipulationValue = 0;
			else if (manipulationValue > magnitudeDistance)
				manipulationValue = magnitudeDistance;
		}
		transformedPoint = vertex1 + (lineVector * manipulationValue);
	}
	else if (manipulationType == ManipulationType::LERP_VALUE)
	{
		if (restrictWithinEdge)
		{
			if (manipulationValue < 0)
				manipulationValue = 0;
			else if (manipulationValue > 1)
				manipulationValue = 1;
		}
		transformedPoint = vertex1 + (lineVector * magnitudeDistance * manipulationValue);
	}
	vertexToMove->x = transformedPoint.x;
	vertexToMove->y = transformedPoint.y;
	vertexToMove->z = transformedPoint.z;
}

VertexManipulationHelper::VertexManipulationHelper()
{
}


VertexManipulationHelper::~VertexManipulationHelper()
{
}
