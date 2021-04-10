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

#include "../objects/object.h"

using namespace std;

template <class T>
class Simulation {
public:
    vector<T> objects;
    vector<GLfloat> vertData;
    vector<GLuint> indexData;
    GLuint VAO, VBO, EBO;
    GLuint count;
    GLfloat cubeLength;
    Simulation(GLfloat cubeLength, GLuint count);

    void create();
    void setBuffers();
    void moveObjects();
    void setData();
    void checkCollisions();
    void draw(Shader shader, glm::vec4 color);
};

#endif