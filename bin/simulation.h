#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "object.h"

using namespace std;

template <class T>
class Simulation {
public:
    vector<T> objects;
    vector<GLfloat> data;
    GLuint VAO, VBO;
    GLuint count;
    GLint MAX_POS = 5.0f;
    Simulation(GLuint count);

    void create();
    void setBuffers();
    void moveObjects();
    void draw(Shader shader);
};

#endif