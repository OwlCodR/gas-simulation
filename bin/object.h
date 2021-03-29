#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Object {
public:
    glm::vec3 position;     // Position of center
    glm::vec3 speed;
    GLfloat mass;           // [kg]
    GLfloat speedScalar;
    GLfloat radius;         // [m]

    Object(){};
    Object(GLfloat mass, GLfloat radius, glm::vec3 position, glm::vec3 speed);

    virtual void move(GLfloat cubeLength) = 0;
};

#endif