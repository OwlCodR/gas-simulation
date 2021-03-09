#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <math.h>

#include "shader.cpp"
#include "shader.h"

// Only for Windows:
#include <Windows.h>
#include <filesystem>

using namespace std;

void error_callback(int error, const char* description) {
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
	//FreeConsole(); // Hide console (Windows)
	initialize();
	glfwSetErrorCallback(error_callback);

	double time = glfwGetTime();
	GLFWwindow* window = glfwCreateWindow(800, 600, "Gas Simulation", nullptr, nullptr);

	if (window == nullptr) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	} else {
		glfwMakeContextCurrent(window);
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glewExperimental = GL_TRUE;
    glewInit();
	
	const GLchar* vertexShaderPath = "./bin/shaders/shader.vert";
	const GLchar* fragmentShaderPath = "./bin/shaders/shader.frag";

	Shader shader(vertexShaderPath, fragmentShaderPath);

	glm::mat4 projection = glm::perspective(45.0f, (float) width / (float) height, 0.1f, 100.0f);
	glm::mat4 model = glm::rotate(model, -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	GLfloat triangles[2][9] = {
		{
			-0.5f, 0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			0.5f,  0.5f, 0.0f
		},
		{
			-0.5f, 0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.7f,  0.0f, 0.0f
		}  
	};

	GLuint VBOs[2], VAOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	
	for (int i = 0; i < 2; i++) {
		glBindVertexArray(VAOs[i]);
			glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]); 
				glBufferData(GL_ARRAY_BUFFER, sizeof(triangles[i]), triangles[i], GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
				glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
	glm::mat4 trans(1.0f);
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		time = glfwGetTime();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (GLfloat) time, glm::vec3(0.0f, 0.0f, 1.0f));

		shader.use();
		
		glUniformMatrix4fv(glGetUniformLocation(shader.program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader.program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glUniform4f(glGetUniformLocation(shader.program, "currentColor"), sin(time), 0.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(glGetUniformLocation(shader.program, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
		glBindVertexArray(VAOs[0]);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		
		glUniformMatrix4fv(glGetUniformLocation(shader.program, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
		glUniform4f(glGetUniformLocation(shader.program, "currentColor"), 0.0f, sin(time), 0.0f, 1.0f);
		glBindVertexArray(VAOs[1]);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		
		
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}