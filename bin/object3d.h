#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

using namespace std;

class Object3D {
private:
    vector<GLfloat> vectorVertices;
    vector<GLuint> vectorIndexes;
    glm::vec3 position;
public:
    GLuint VAO, VBO, EBO;

    virtual void create() = 0;
    virtual void setBuffers() = 0;
    virtual void draw(Shader shader, glm::vec4 color, int mode) = 0;

    virtual vector<GLfloat>& getVertices() {
        return this->vectorVertices;
    }

    virtual vector<GLuint>& getIndexes() {
        return this->vectorIndexes;
    }

    virtual glm::vec3 getPosition() {
        return this->position;
    }
    virtual void setPosition(glm::vec3 position) {
        this->position = position;
    }
};

#endif