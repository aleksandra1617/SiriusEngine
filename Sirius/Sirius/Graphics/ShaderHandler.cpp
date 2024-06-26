#include "ShaderHandler.h"


// Using an initialization list here because it's faster than _program = 0
ShaderHandler::ShaderHandler()
{
}


ShaderHandler::~ShaderHandler()
{
}


void ShaderHandler::LinkProgram(GLuint& program)
{
	//CREATES A VERTEX SHADER HANDLER
	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, "./Graphics/Shaders/TriangleShader.vs");

	//CREATES A FRAGMENT SHADER HANDLER
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, "./Graphics/Shaders/TriangleShader.fs");

	program = glCreateProgram();

	//LINK Shaders
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	
	CheckLink(program);

	//CLEANUP
	glDeleteShader(fragmentShader);
	glDetachShader(program, fragmentShader);
	glDeleteShader(vertexShader);
	glDetachShader(program, vertexShader);
}

void ShaderHandler::CheckLink(GLuint& program)
{
	GLint link_status;
	glGetProgramiv(program, GL_LINK_STATUS, &link_status);

	std::cout << "Link status: " << link_status << std::endl;

	if (link_status != GL_TRUE)
	{
		const int string_length = 1024;
		GLchar errorLog[string_length] = "";
		glGetProgramInfoLog(program, string_length, NULL, errorLog);
		std::cout << "Error Detected in LinkProgram()" << std::endl; 
		std::cerr << errorLog << std::endl;
	}
	else
	{
		std::cout << "Successful Link Established!" << std::endl;
	}
}


std::string ShaderHandler::ReadShaderString(const std::string &path) 
{
	std::string data;
	std::string line;

	std::ifstream shaderFile;
	shaderFile.open((path).c_str());

	if (shaderFile.is_open())
	{
		//while there's more to read
		while (shaderFile.good())
		{
			getline(shaderFile, line);
			data.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load the (" << path << ") shader file!" << std::endl;
	}

	return data;
}


GLuint ShaderHandler::CreateShader(GLenum shaderType, const std::string &path)
{
	GLuint shader = glCreateShader(shaderType);
	std::string shaderData = ReadShaderString(path);

	const char * shaderCode = shaderData.c_str();
	glShaderSource(shader, 1, (const GLchar **)&shaderCode, NULL);
	glCompileShader(shader);

	CheckShaderCompilation(shader);

	return shader;
}


bool ShaderHandler::CheckShaderCompilation(GLuint shader)
{
	GLint compile_status = GL_FALSE;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

	if (compile_status != GL_TRUE)
	{
		const int string_length = 1024;
		GLchar log[string_length] = "";
		glGetShaderInfoLog(shader, string_length, NULL, log);
		std::cout << "Error Detected in CreateShader()";
		std::cerr << log << std::endl;

		return false;
	}
	else
	{
		std::cout << "Shader: " << shader << " compiled successfully. " << std::endl;
	}

	return true;
}