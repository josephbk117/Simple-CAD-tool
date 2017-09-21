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
	ADDING_VERTICES, EDITING_VERTICES, MODEL_CYCLE_THROUGH
};

bool showLocalSpace = false;

InteractionModes currentInteractionMode = InteractionModes::ADDING_VERTICES;

void framebuffer_size_callback(GLFWwindow * window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow * window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

Camera camera(glm::vec3(0.0f, 0.0f, -20.0f));
float lastX = 500 / 2.0f;
float lastY = 500 / 2.0f;
bool firstMouse = true;

struct MouseData
{
	int x, y;
	bool isLeftButtonPressed;
}mouseData;

GLFWwindow *window;
std::vector<Model *> models;
Model* activeModel;
Viewport* activeViewport;
Viewport* viewports[4];
std::vector<vec4 *>currentlyHeldVertices;
int currentlyActiveModelIndex = 0;

int main()
{
	mouseData.isLeftButtonPressed = false;
	glfwInit();
	window = glfwCreateWindow(500, 500, "Open Gl - Simple CAD Tool", NULL, NULL);
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
	glfwSetKeyCallback(window, keyboard_callback);
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
	shader.addAttribute("aVert");
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

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	projection = glm::orthoLH(-125.0f, 125.0f, -125.0f, 125.0f, -200.0f, 200.0f);

	shader.use();
	shader.setMat4("model", model);
	shader.setMat4("projection", projection);
	while (!glfwWindowShouldClose(window))
	{
		timeValue += 0.001f;
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		viewportBottomLeft.show(glm::translate(glm::mat4(),
			glm::vec3(0, 0, 30)), models, currentlyActiveModelIndex, showLocalSpace);
		viewportTopRight.show(glm::rotate(glm::mat4(),
			glm::radians(90.0f), glm::vec3(0, 1, 0)) * glm::translate(glm::mat4(),
				glm::vec3(30, 0, 0)), models, currentlyActiveModelIndex, showLocalSpace);
		viewportBottomRight.show(glm::rotate(glm::mat4(),
			glm::radians(90.0f), glm::vec3(1, 0, 0))*glm::rotate(glm::mat4(), glm::radians(90.0f), glm::vec3(0, 1, 0)) * glm::translate(glm::mat4(),
				glm::vec3(0, 30, 0)), models, currentlyActiveModelIndex, showLocalSpace);
		viewportTopLeft.show(glm::rotate(glm::mat4(), (float)glfwGetTime(),
			glm::vec3(1, 1, 1)) * glm::translate(glm::mat4(),
				glm::vec3(30, 0, 0)), models, currentlyActiveModelIndex, showLocalSpace);

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

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		activeModel->translate(vec3(0, 1, 0));
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		activeModel->translate(vec3(0, -1, 0));
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		activeModel->translate(vec3(1, 0, 0));
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		activeModel->translate(vec3(-1, 0, 0));
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		activeModel->translate(vec3(0, 0, -1));
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		activeModel->translate(vec3(0, 0, 1));
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	mouseData.x = (int)xpos;
	mouseData.y = -(int)ypos;
	for (int i = 0; i < 4; i++)
	{
		viewports[i]->setBorderColor(0, 0.5, 1);
		if (viewports[i]->isPointInViewport(mouseData.x, mouseData.y))
			activeViewport = viewports[i];
		else
			viewports[i]->setBorderColor(1, 1, 1);
	}
	float x1 = mouseData.x, y1 = mouseData.y;
	if (mouseData.isLeftButtonPressed)
	{
		if (currentlyHeldVertices.size() > 0 && currentInteractionMode == InteractionModes::EDITING_VERTICES)
		{
			activeViewport->getConvertedViewportCoord(x1, y1);
			if (activeViewport == viewports[0])
			{
				if (currentlyHeldVertices.size() == 1)
				{
					currentlyHeldVertices[0]->x = x1;
					currentlyHeldVertices[0]->y = y1;
				}
			}
			else if (activeViewport == viewports[2])
			{
				if (currentlyHeldVertices.size() == 1)
				{
					currentlyHeldVertices[0]->y = y1;
					currentlyHeldVertices[0]->z = x1;
				}
			}
			else if (activeViewport == viewports[3])
			{
				if (currentlyHeldVertices.size() == 1)
				{
					currentlyHeldVertices[0]->x = y1;
					currentlyHeldVertices[0]->z = x1;
				}
			}
			activeModel->updateMeshData();
		}
	}
}
void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_Z)
			currentInteractionMode = InteractionModes::ADDING_VERTICES;
		if (key == GLFW_KEY_X)
		{
			if (activeModel->containsVertexData())
			{
				models.push_back(activeModel = new Model);
				currentlyActiveModelIndex = models.size() - 1;
				currentInteractionMode = InteractionModes::ADDING_VERTICES;
			}
		}
		if (key == GLFW_KEY_C)
		{
			currentlyHeldVertices.clear();
			activeModel->clearSelectedVertcies();
			activeModel->updateMeshData();
			currentInteractionMode = InteractionModes::EDITING_VERTICES;
		}
		if (key == GLFW_KEY_DELETE)
		{
			for (int i = 0; i < currentlyHeldVertices.size(); i++)
				activeModel->removeVertex(currentlyHeldVertices[i], activeModel);
			activeModel->updateMeshData();
			currentInteractionMode = InteractionModes::ADDING_VERTICES;
		}
		if (key == GLFW_KEY_E && currentInteractionMode == InteractionModes::EDITING_VERTICES)
		{
			if (currentlyHeldVertices.size() > 0)
			{
				for (int i = 0; i < currentlyHeldVertices.size(); i++)
				{
					unsigned int indexOfVertex = activeModel->getIndexOfVertex(currentlyHeldVertices[i]);
					activeModel->addVertexFlowSplitIndex(indexOfVertex + 1);
					activeModel->addVertex(vec3(currentlyHeldVertices[i]->x, currentlyHeldVertices[i]->y, currentlyHeldVertices[i]->z), indexOfVertex);
				}
				activeModel->updateMeshData();
				currentInteractionMode = InteractionModes::ADDING_VERTICES;
			}
		}
		if (key == GLFW_KEY_Q)
		{
			showLocalSpace = !showLocalSpace;
		}
		if (key == GLFW_KEY_N || key == GLFW_KEY_M)
		{
			currentlyActiveModelIndex = (key == GLFW_KEY_N) ? currentlyActiveModelIndex - 1 : currentlyActiveModelIndex + 1;
			if (currentlyActiveModelIndex > models.size() - 1)
				currentlyActiveModelIndex = 0;
			if (currentlyActiveModelIndex < 0)
				currentlyActiveModelIndex = models.size() - 1;
			activeModel = models[currentlyActiveModelIndex];
		}
	}
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		mouseData.isLeftButtonPressed = true;
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
			if (currentlyHeldVertices.size() <= 0)
			{
				activeViewport->getConvertedViewportCoord(x1, y1);
				vec4* vertex = nullptr;
				if (activeViewport == viewports[0])
					vertex = activeModel->vertexAtViewportCoord(x1, y1, NULL);
				if (activeViewport == viewports[2])
					vertex = activeModel->vertexAtViewportCoord(NULL, y1, x1);
				if (activeViewport == viewports[3])
					vertex = activeModel->vertexAtViewportCoord(y1, NULL, x1);
				if (vertex != nullptr)
					currentlyHeldVertices.push_back(vertex);
			}
			std::vector<unsigned int> indices;
			for (int i = 0; i < currentlyHeldVertices.size(); i++)
				indices.push_back(activeModel->getIndexOfVertex(currentlyHeldVertices[i]));
			activeModel->setVerticesAsSelected(indices);
		}
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action != GLFW_PRESS)
		mouseData.isLeftButtonPressed = false;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}