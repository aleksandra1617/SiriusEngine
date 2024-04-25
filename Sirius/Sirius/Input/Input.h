#pragma once

struct GLFWwindow;

class Input
{
public:
	Input();
	~Input();

	bool Init();
	void ProcessInput(GLFWwindow* window);
};