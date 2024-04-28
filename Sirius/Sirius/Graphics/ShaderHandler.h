#pragma once

#include <iostream>
#include <fstream> 
#include <vector>
#include <map>
#include <string> 
#include <glad\glad.h>

class ShaderHandler
{
public:
	ShaderHandler();
	~ShaderHandler();

	/**
	*	@brief	Links shaders to a program. 
	* 
	*   Creates a program object to host the shaders and their settings.
	*   The program object attempts to bind the shaders
	*   together when it is linked. If the shaders aren't compatible
	*   the link process will fail. Once the program gets the shader
	*   stage information, the shaders can be detached and deleted.
	*/
	void LinkProgram(GLuint& program);

private:

	/**
	*	@brief	Queries program link errors via the OpenGL's info log.
	*/
	void CheckLink(GLuint& program);

	/**
	*   @brief	Reads text from a given file.
	*/
	std::string ReadShaderString(const std::string &path);

	/** 
	*	@brief	Reads the shader string, creates a shader object and attempts to compile it. 
	*/
	GLuint CreateShader(GLenum shaderType, const std::string &path);

	/**
	*	@brief	Queries shader compile errors via the OpenGL's info log.
	*/
	bool CheckShaderCompilation(GLuint shader);
};

