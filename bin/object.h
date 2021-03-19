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
    glm::vec2 position;
    glm::vec2 direction;

    Object(){};
    Object(glm::vec2 position, glm::vec2 direction);

    virtual void move(GLfloat MAX_POS) = 0;
};

#endif