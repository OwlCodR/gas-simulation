#define GLEW_STATIC
#include <GL/glew.h>
//#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "SOIL/SOIL.h" 

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <math.h>

#include "shader.cpp"
#include "shader.h"

#include "sphere.cpp"
#include "sphere.h"


#include "cylinder.h"
#include "cylinder.cpp"

using namespace std;

float speed = 0.1f;
bool keys[1024];

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    	glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}

void moveView(glm::mat4& view) {
	glm::vec3 deltaVec(0.0f, 0.0f, 0.0f);

	if (keys[GLFW_KEY_W])
		deltaVec.z += speed;
	else if (keys[GLFW_KEY_S])
    	deltaVec.z -= speed;

	if (keys[GLFW_KEY_A])
    	deltaVec.x += speed;
	else if (keys[GLFW_KEY_D])
    	deltaVec.x -= speed;
	
	view = glm::translate(view, deltaVec);
}

void initialize() {
	if (!glfwInit())
        exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwSwapInterval(0);

	glEnable(GL_DEPTH_TEST | GL_MULTISAMPLE);

}

int main()
{
	double time = glfwGetTime();
	initialize();

	GLFWwindow* window = glfwCreateWindow(800, 600, "Gas Simulation", nullptr, nullptr);
	
	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(window, key_callback); 

	if (window == nullptr) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	} else {
		glfwMakeContextCurrent(window);
	}

	int w, h;
	unsigned char* image = SOIL_load_image("./textures/stone.jpg", &w, &h, 0, SOIL_LOAD_RGB);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glewExperimental = GL_TRUE;
	glewInit();
	
	const GLchar* vertexShaderPath = "./bin/shaders/shader.vert";
	const GLchar* fragmentShaderPath = "./bin/shaders/shader.frag";

	Shader shader(vertexShaderPath, fragmentShaderPath);

	glm::mat4 projection(1.0f);
	projection = glm::perspective(45.0f, (float) width / (float) height, 0.1f, 100.0f);
	glm::mat4 model(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 view(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	// GLfloat vertices[] = {
    //     0,   0.5,   0,
	// 	0.5,   -2.18557e-08,   0,
	// 	-2.18557e-08,   -2.18557e-08,   0.5,
	// 	-0.5,   -2.18557e-08,   -4.37114e-08,
	// 	5.96244e-09,   -2.18557e-08,   -0.5,
	// 	-4.37114e-08,   -0.5,   0
    // };
	
	// GLuint indices[] = {
    //     0,   1,   2,
	// 	0,   2,   3,
	// 	0,   3,   4,
	// 	0,   4,   1,
	// 	5,   4,   3,
	// 	5,   3,   2,
	// 	5,   2,   1,
	// 	5,   1,   4
    // };

	Sphere sphere1(glm::vec3(4.0f, 0.0f, 0.0f), 1.0f, 100, 100);
	Sphere sphere2(glm::vec3(-4.0f, 0.0f, 0.0f), 1.0f, 100, 100);
	Sphere sphere3(glm::vec3(0.0f, -4.0f, 0.0f), 1.0f, 100, 100);
	Sphere sphere4(glm::vec3(0.0f, 4.0f, 0.0f), 1.0f, 100, 100);
	Sphere sphere5(glm::vec3(0.0f, 0.0f, -4.0f), 1.0f, 100, 100);
	Sphere sphere6(glm::vec3(0.0f, 0.0f, 4.0f), 1.0f, 100, 100);

	Cylinder square(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f * glm::sqrt(2), 4);
	
	time = glfwGetTime();
	sphere1.create();
	sphere2.create();
	sphere3.create();
	sphere4.create();
	sphere5.create();
	sphere6.create();

	square.create();

	cout << "\nCreating time: " << glfwGetTime() - time << endl;
	
	sphere1.setBuffers();
	sphere2.setBuffers();
	sphere3.setBuffers();
	sphere4.setBuffers();
	sphere5.setBuffers();
	sphere6.setBuffers();

	square.setBuffers();
	
	glm::vec4 color(1.0f);
	color = glm::vec4(((float) sin(time)), 0.5f, 1.0f, 1.0f);

	double lastTime = glfwGetTime();
 	int nbFrames = 0;

	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents(); 

		double currentTime = glfwGetTime();
		nbFrames++;
		if ( currentTime - lastTime >= 1.0 ) {
			//printf("%f ms/frame\n", double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		moveView(view);
		
		shader.use();

		model = glm::rotate(model, 0.01f, glm::vec3(0.0f, 0.0f, 1.0f));
		
		glUniformMatrix4fv(glGetUniformLocation(shader.program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader.program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		color.r = sin(glfwGetTime());
		sphere1.draw(shader, color, GL_TRIANGLES);
		sphere2.draw(shader, color, GL_TRIANGLES);
		sphere3.draw(shader, color, GL_TRIANGLES);
		sphere4.draw(shader, color, GL_TRIANGLES);
		sphere5.draw(shader, color, GL_TRIANGLES);
		sphere6.draw(shader, color, GL_TRIANGLES);

		model = glm::mat4(1.0f);
		//glUniformMatrix4fv(glGetUniformLocation(shader.program, "model"), 1, GL_FALSE, glm::value_ptr(model));

		square.draw(shader, color, GL_TRIANGLES);

		
		
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}