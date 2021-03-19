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
    Particle(glm::vec2 position, glm::vec2 direction);

    void move(GLfloat MAX_POS) override;
};

#endif