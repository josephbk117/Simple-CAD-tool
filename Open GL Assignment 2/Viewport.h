#pragma once
#include <GLM\glm.hpp>
#include "ShaderProgram.h"
#include <vector>
#include "Model.h"
using namespace glm;

class Viewport
{
public:
	enum class ViewAxis
	{
		X_Y, Y_Z, Z_X
	};
	Viewport(vec2 origin, vec2 size, const ShaderProgram& shaderProgram);
	void setViewAxis(ViewAxis viewAxis);
	void setViewMatrix(mat4 viewMatrix);
	void show(const mat4 &viewMatrix, const std::vector<Model *> &models, unsigned int activeModelIndex, bool showLocalSpace);
	void setViewportConvertion(float xOffset, float yOffset);
	void getConvertedViewportCoord(float &x, float &y);
	void setBorderColor(float r, float g, float b);
	bool isPointInViewport(int x, int y);
	~Viewport();
private:
	ViewAxis viewAxis;
	vec2 origin;
	vec2 size;
	ShaderProgram shader;
	vec3 borderColour;
	float xOffset, yOffset;
	void drawBorder();
	void drawViewAxis();
};