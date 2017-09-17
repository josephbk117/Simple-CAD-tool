#pragma once
#include <iostream>
#include <GL\glew.h>
#include <fstream>
#include <string>
#include <GLM/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	void compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	void linkShaders();
	void addAttribute(const std::string& attributeName);
	void use();
	void unuse();
	void setMat4(const std::string & name, glm::mat4 value);
	void setVec3(const std::string & name, glm::vec3 value);
	GLint getUniformLocation(const std::string& uniformName);
	GLuint getShaderID();
private:
	GLuint programID, vertexShaderID, fragmentShaderID;
	void compileShader(const std::string& filePath, GLuint ID);
	int attributeCount;
};
