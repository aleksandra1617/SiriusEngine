#include "Input.h"

#include <GLFW/glfw3.h>

Input::Input()
{
}

Input::~Input()
{
}

bool Input::Init()
{
	return false;
}

void Input::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	glfwPollEvents();
}
