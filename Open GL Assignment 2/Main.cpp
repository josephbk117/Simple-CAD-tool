#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "Camera.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "Viewport.h"
#include <vector>

enum InteractionModes
{
	ADDING_VERTICES, CREATING_NEW_MODEL, EDITING_VERTICES
};

InteractionModes currentInteractionMode = InteractionModes::ADDING_VERTICES;

void framebuffer_size_callback(GLFWwindow * window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow * window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

Camera camera(glm::vec3(0.0f, 0.0f, -20.0f));
float lastX = 500 / 2.0f;
float lastY = 500 / 2.0f;
bool firstMouse = true;

struct MouseData
{
	int x, y;
}mouseData;

GLFWwindow *window;
std::vector<Model *> models;
Model* activeModel;
Viewport* activeViewport;
Viewport* viewports[4];
vec3* currentlyHeldVertex = nullptr;

int main()
{
	glfwInit();
	window = glfwCreateWindow(500, 500, "LOLZ", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	GLenum err = glewInit();
	glEnable(GL_DEPTH_TEST);
	if (GLEW_OK != err)
		std::cout << "Error: \n" << glewGetErrorString(err);
	else
		std::cout << " Glew initialsed" << std::endl;

	Model vertexObj;
	models.push_back(&vertexObj);
	activeModel = &vertexObj;

	ShaderProgram shader;
	shader.compileShaders("F:\\Visual Studio 2017\\Projects\\Open GL Assignment 2\\Debug\\basic.vs",
		"F:\\Visual Studio 2017\\Projects\\Open GL Assignment 2\\Debug\\basic.fs");
	shader.addAttribute("aPos");
	shader.linkShaders();

	Viewport viewportBottomLeft(vec2(0, 0), vec2(250, 250), shader);
	Viewport viewportTopLeft(vec2(0, 250), vec2(250, 250), shader);
	Viewport viewportTopRight(vec2(250, 250), vec2(250, 250), shader);
	Viewport viewportBottomRight(vec2(250, 0), vec2(250, 250), shader);

	viewportBottomLeft.setViewportConvertion(-(500 / 4), (500 / 2) + (500 / 4));
	viewportBottomRight.setViewportConvertion(-500 + (500 / 4), (500 / 2) + (500 / 4));
	viewportTopRight.setViewportConvertion(-500 + (500 / 4), (500 / 4));
	viewportTopLeft.setViewportConvertion(-(500 / 4), (500 / 4));
	activeViewport = &viewportBottomLeft;

	viewports[0] = &viewportBottomLeft;
	viewports[1] = &viewportTopLeft;
	viewports[2] = &viewportTopRight;
	viewports[3] = &viewportBottomRight;

	camera.Position = vec3(0, 0, 3);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	float timeValue = 0;
	while (!glfwWindowShouldClose(window))
	{
		timeValue += 0.001f;
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		projection = glm::orthoLH(-125.0f, 125.0f, -125.0f, 125.0f, -150.0f, 150.0f);

		shader.use();
		shader.setMat4("model", model);
		shader.setMat4("projection", projection);

		viewportBottomLeft.show(glm::translate(glm::mat4(),
			glm::vec3(0, 0, 30)), models);
		viewportTopRight.show(glm::rotate(glm::mat4(),
			glm::radians(90.0f), glm::vec3(0, 1, 0)) * glm::translate(glm::mat4(),
				glm::vec3(30, 0, 0)), models);
		viewportBottomRight.show(glm::rotate(glm::mat4(),
			glm::radians(90.0f), glm::vec3(1, 0, 0))*glm::rotate(glm::mat4(), glm::radians(90.0f), glm::vec3(0, 1, 0)) * glm::translate(glm::mat4(),
				glm::vec3(0, 30, 0)), models);
		viewportTopLeft.show(glm::rotate(glm::mat4(), (float)glfwGetTime(),
			glm::vec3(2.2f, 3.4, 0.4f)) * glm::translate(glm::mat4(),
				glm::vec3(30, 0, 0)), models);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
void processInput(GLFWwindow * window)
{
	/*if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);*/
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		currentInteractionMode = InteractionModes::ADDING_VERTICES;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		currentInteractionMode = InteractionModes::CREATING_NEW_MODEL;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		currentInteractionMode = InteractionModes::EDITING_VERTICES;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		currentlyHeldVertex = nullptr;

}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	mouseData.x = (int)xpos;
	mouseData.y = -(int)ypos;
	for (int i = 0; i < 4; i++)
	{
		viewports[i]->setBorderColor(1, 0.5, 1);
		if (viewports[i]->isPointInViewport(mouseData.x, mouseData.y))
		{
			viewports[i]->setBorderColor(0, 0.5, 1);
			activeViewport = viewports[i];
		}
		else
			viewports[i]->setBorderColor(1, 1, 1);
	}
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		float x1 = mouseData.x, y1 = mouseData.y;
		if (currentInteractionMode == InteractionModes::ADDING_VERTICES)
		{
			activeViewport->getConvertedViewportCoord(x1, y1);
			if (activeViewport == viewports[0])
				activeModel->addVertex(x1, y1, 0);
			else if (activeViewport == viewports[2])
				activeModel->addVertex(0, y1, x1);
			else if (activeViewport == viewports[3])
				activeModel->addVertex(y1, 0, x1);
			activeModel->updateMeshData();
		}
		else if (currentInteractionMode == InteractionModes::EDITING_VERTICES)
		{
			//FOR NOW
			if (currentlyHeldVertex == nullptr)
			{
				if (activeViewport == viewports[0])
				{
					std::cout << "\ncurrently held is null";
					activeViewport->getConvertedViewportCoord(x1, y1);
					currentlyHeldVertex = models[0]->vertexAtViewportCoord(x1, y1, 0);
				}
				if (activeViewport == viewports[2])
				{
					activeViewport->getConvertedViewportCoord(x1, y1);
					currentlyHeldVertex = models[0]->vertexAtViewportCoord(0, y1, x1);
				}
			}
			else if (currentlyHeldVertex != nullptr)
			{
				std::cout << "\ncurrently held is not null";
				activeViewport->getConvertedViewportCoord(x1, y1);
				currentlyHeldVertex->x = x1;
				currentlyHeldVertex->y = y1;
				currentlyHeldVertex->z = currentlyHeldVertex->z;
				activeModel->updateMeshData();
				std::cout << "\new vertex position is " << x1 << " ," << y1;
			}
		}
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}