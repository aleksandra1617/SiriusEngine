#include "Renderer.h"

#include "ShaderHandler.h"
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
	_shaderHandler = new ShaderHandler();
}

Renderer::~Renderer()
{
	Cleanup();
}

bool Renderer::Init()
{
	_graphicsStage = GraphicsStage::INIT;

	_mainWindow = CreateWindow();
	_shaderHandler->LinkProgram(_shaderProgram);
	glUseProgram(_shaderProgram);


	// Set up vertex data buffer(s) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attributes' bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// uncomment this call to draw in wire frame polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	return true;
}

void Renderer::Cleanup()
{
	glDeleteBuffers(1, &_vbo);

	glfwSetWindowShouldClose(_mainWindow, true);
	glfwTerminate();
}

void Renderer::Render()
{
	glClearColor(0.18f, 0.16f, 0.34f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	//DRAW Geometry
	glBindVertexArray(_vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// glBindVertexArray(0); // no need to unbind it every time 

	glfwSwapBuffers(_mainWindow);
}

GLFWwindow* Renderer::CreateWindow()
{
	InitGLFW();

	GLFWwindow* window = glfwCreateWindow(_winWidth, _winHight, "Sirius Engine", nullptr, nullptr);

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

	// GLAD loads all OpenGL function pointers.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return nullptr;
	}

	glViewport(0, 0, _winWidth, _winHight);

	// Log the OGL Version
	std::cout << glGetString(GL_VERSION) << std::endl;

	return window;
}

bool Renderer::InitGLFW()
{
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

	return true;
}
