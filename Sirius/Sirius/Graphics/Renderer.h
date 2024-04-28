#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct GLFWwindow;

class ShaderHandler;

/// Will be used to create loading bar and keep track of what the graphics system is doing. 
enum class GraphicsStage { NONE, INIT, LOAD_VERT_DATA, COMPILE_SHADERS, RENDER };

/// Handles rendering. 
class Renderer
{
public:
	Renderer(int winWidth = 1024, int winHight = 720);
	~Renderer();

	bool Init();	
	virtual void Render();
	void Cleanup();

	GLFWwindow* GetMainWindow() { return _mainWindow; }

	bool IsWindowClosing() 
	{
		return glfwWindowShouldClose(_mainWindow);
	};

protected:
	GLFWwindow* _mainWindow;

	GLFWwindow* CreateWindow();

private:
	int _winWidth, _winHight;

	/*
	*	Use GLuint for IDs.
	*/
	GLuint _vbo, _vao; //Vertex Buffer Object ID and Vertex Array Object ID
	GLuint _shaderProgram;
	GraphicsStage _graphicsStage;	
	
	ShaderHandler* _shaderHandler;

	bool InitGLFW();
};