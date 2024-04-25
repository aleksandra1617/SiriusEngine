#include "Renderer.h"

#include <iostream>

/*
* This function is free because it is a registered callback for the glfwFramebuffer.
*/ 
void FramebufferResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Renderer::Renderer(int winWidth, int winHight) : 
	_winWidth(winWidth), 
	_winHight(winHight), 
	_graphicsStage(GraphicsStage::NONE)
{
}

Renderer::~Renderer()
{
	Cleanup();
}

bool Renderer::Init()
{
	_graphicsStage = GraphicsStage::INIT;

	//INITIALIZE and CONFIG GLFW
	GLuint glfwStatus = glfwInit();

	//CHECK if initialized correctly
	if (glfwStatus != GLFW_TRUE) 
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	_mainWindow = CreateWindow();

	if (!_mainWindow)
		return false;

	// GLAD loads all OpenGL function pointers.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glViewport(0, 0, _winWidth, _winHight);

	// Log the OGL Version
	std::cout << glGetString(GL_VERSION) << std::endl;

	return true;
}

void Renderer::Cleanup()
{
	glfwSetWindowShouldClose(_mainWindow, true);
	glfwTerminate();
}

void Renderer::Render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(_mainWindow);
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

	//CREATE Context (allows the GPU to draw on the window)
	glfwMakeContextCurrent(window);

	// REGISTER CALLBACK for resizing the viewport when the window is resized. 
	glfwSetFramebufferSizeCallback(window, FramebufferResizeCallback);

	return window;
}
