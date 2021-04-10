#ifndef PARTICLE_H
#define PARTICLE_H

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "object.h"

using namespace std;

class Particle : public Object {
public:
    Particle(GLfloat mass, GLfloat radius, glm::vec3 position, glm::vec3 speed);
    void move(GLfloat cubeLength) override;

    static void setBuffers(GLuint VAO, GLuint VBO, GLuint EBO);
    static void draw(GLfloat cubeLength);
};

#endif