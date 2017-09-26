#include "Viewport.h"

Viewport::Viewport(vec2 origin, vec2 size, const ShaderProgram& shaderProgram)
{
	this->origin = origin;
	this->size = size;
	this->shader = shaderProgram;
	borderColour = vec3(1, 1, 1);
	xOffset = 0;
	yOffset = 0;
}

void Viewport::setViewAxis(ViewAxis viewAxis)
{
	this->viewAxis = viewAxis;
}

void Viewport::setViewMatrix(mat4 viewMatrix)
{
	shader.setMat4("view", viewMatrix);
}

void Viewport::show(const mat4 &viewMatrix, const std::vector<Model *> &models, unsigned int activeModelIndex, bool showLocalSpace)
{
	glViewport(origin.x, origin.y, size.x, size.y);
	shader.use();
	shader.setMat4("view", viewMatrix);
	for (int i = 0; i < models.size(); i++)
	{
		if (i == activeModelIndex)
		{
			if (!showLocalSpace)
				shader.setVec3("colour", glm::vec3(0.7, 0.25, 0.85));
			else
				shader.setInt("togglePosColour", 1);
			models[i]->display(true, &shader);
		}
		else
		{
			shader.setVec3("colour", glm::vec3(0.2, 0.95, 0.95));
			shader.setInt("togglePosColour", 0);
			models[i]->display(false, &shader);
		}
	}
	shader.unuse();
	drawBorder();
	drawViewAxis();
}

void Viewport::setViewportConvertion(float xOffset, float yOffset)
{
	this->xOffset = xOffset;
	this->yOffset = yOffset;
}

void Viewport::getConvertedViewportCoord(float & x, float & y)
{
	x = x + xOffset;
	y = y + yOffset;
}

void Viewport::setBorderColor(float r, float g, float b)
{
	borderColour = vec3(r, g, b);
}

bool Viewport::isPointInViewport(int x, int y)
{
	if (x + xOffset >= -125 && x + xOffset <= 125 && y + yOffset >= -125 && y + yOffset <= 125)
		return true;
	return false;
}

Viewport::~Viewport()
{
}

void Viewport::drawBorder()
{
	glLineWidth(3);
	glColor3f(borderColour.r, borderColour.g, borderColour.b);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.999, 0.999);
	glVertex2f(0.999, -0.999);
	glVertex2f(-0.999, -0.999);
	glVertex2f(-0.999, 0.999);
	glEnd();
	glColor3f(1, 1, 1);
	glLineWidth(1);
}

void Viewport::drawViewAxis()
{
	glLineWidth(2);
	glBegin(GL_LINES);
	if (viewAxis == ViewAxis::X_Y)
	{
		//__Y__
		glColor3f(0.2, 0.9, 0);
		glVertex2f(0.6f, -0.9f);
		glVertex2f(0.6f, -0.6f);
		//__X__
		glColor3f(0.9, 0.2, 0);
		glVertex2f(0.6f, -0.9f);
		glVertex2f(0.9f, -0.9f);
	}
	else if (viewAxis == ViewAxis::Z_X)
	{
		glColor3f(0.9, 0.2, 0);
		glVertex2f(0.6f, -0.9f);
		glVertex2f(0.6f, -0.6f);

		glColor3f(0, 0.2, 0.9);
		glVertex2f(0.6f, -0.9f);
		glVertex2f(0.9f, -0.9f);
	}
	else if (viewAxis == ViewAxis::Y_Z)
	{
		glColor3f(0.2, 0.9, 0);
		glVertex2f(0.6f, -0.9f);
		glVertex2f(0.6f, -0.6f);

		glColor3f(0.0, 0.2, 0.9);
		glVertex2f(0.6f, -0.9f);
		glVertex2f(0.9f, -0.9f);
	}
	glEnd();
	glLineWidth(1);
}
