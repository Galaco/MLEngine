#ifndef SHADER_H
#define SHADER_H

#include "../Assert/Assert.h"
#include "..\Interfaces\IResource.h"
#include "GL\glew.h"
#include "GLM\glm.hpp"
#include "GLFW\glfw3.h"
#include "..\File\FileManager.h"
#include <string>
#include <map>

class Shader : public IResource
{
public:
	Shader();
	Shader(std::string path);

	~Shader();
	
	virtual bool LoadFromFile(std::string filename);
	
	bool SendUniformMat4(const char* uniformName, const glm::mat4 matrix);
	bool SendUniformMat3(const char* uniformName, const glm::mat3 matrix);
	bool SendUniformVec4(const char* uniformName, const glm::vec4 vector);
	bool SendUniformVec3(const char* uniformName, const glm::vec3 vector);

	void UseShader();

private:
	GLint GetUniformLocation(const char* uniformName);
	bool CompileAndLinkShader(std::string vertShader, std::string fragShader, GLuint& programID);

	bool CompileShader(GLuint shaderID);
	bool LinkShader(GLuint shaderID);

	GLuint loadedShaderProgramID;
	std::string vertexSource;
	std::string fragmentSource;
	std::map<const char*, GLint> uniformCache;
};

#endif