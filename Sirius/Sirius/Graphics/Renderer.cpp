#include "Renderer.h"

#include <iostream>


Renderer::Renderer(int winWidth, int winHight) : 
	_winWidth(winWidth), 
	_winHight(winHight), 
	_graphicsStage(GraphicsStage::NONE)
{
}

Renderer::~Renderer()
{
	EndRender();
}

bool Renderer::Init()
{
	_graphicsStage = GraphicsStage::INIT;

	//INITIALIZE and CONFIG GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	_mainWindow = CreateWindow();

	if (!_mainWindow)
		return false;

	// INITIALIZE GLAD after the main window is created.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glViewport(0, 0, _winWidth, _winHight);

	return true;
}

void Renderer::Update()
{
	Render();
	
	glfwSwapBuffers(_mainWindow);
	glfwPollEvents(); //TODO: Move into input handler
}

void Renderer::EndRender()
{
	glfwSetWindowShouldClose(_mainWindow, true);
	glfwTerminate();
}

void Renderer::Render()
{
	
}

GLFWwindow* Renderer::CreateWindow()
{
	GLFWwindow* window = glfwCreateWindow(_winWidth, _winHight, "SiriusEngine", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return nullptr;
	}

	glfwMakeContextCurrent(window);

	return window;
}
