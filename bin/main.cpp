#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <math.h>

// Only for Windows:
#include <Windows.h>

using namespace std;

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void initialize() {
	if (!glfwInit())
        exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

int main()
{
	FreeConsole(); // Hide console

	glfwSetErrorCallback(error_callback);

	initialize();

	GLFWwindow* window = glfwCreateWindow(800, 600, "Gas Simulation", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glfwMakeContextCurrent(window);

	double time = glfwGetTime();
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		time = glfwGetTime();

		/*
		* Draw here!
		*/

		glClearColor(0.2f * sin(time), 0.7f * sin(time), 0.8f * cos(time), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}