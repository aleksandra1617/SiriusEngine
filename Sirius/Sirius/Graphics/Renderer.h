#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct GLFWwindow;

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
	*	Defining integer constants to improve readability. Any integers
	*	found in the code should be counting numbers, not ids.
	*/
	const int _NULLID{ 0 };
	unsigned int _vbo; //Vertex Buffer Object ID

	GraphicsStage _graphicsStage;
};