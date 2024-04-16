// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>

#include "GameWorld.h"

int main()
{
//	//INITIALIZE and CONFIG GLFW
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//	//CREATE a window
//	GLFWwindow* window = glfwCreateWindow(800, 600, "SiriusEngine", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	glfwMakeContextCurrent(window);
//
//	// INITIALIZE GLAD before calling any OpenGL functions.
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	glViewport(0, 0, 800, 600);
//	
//	//MAIN LOOP
//	while (!glfwWindowShouldClose(window))
//	{
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	//CLEANUP
//	glfwTerminate();

	GameWorld* world = new GameWorld();
	world->InitSystems();
	world->Update();

	return 0;
}