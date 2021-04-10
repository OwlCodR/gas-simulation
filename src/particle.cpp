#include "particle.h"

Particle::Particle(GLfloat mass, GLfloat radius, glm::vec3 position, glm::vec3 speed) {
    this->mass = mass;
    this->radius = radius;
    this->position = position;
    this->speed = speed;
}

void Particle::move(GLfloat cubeLength) {
    for (int i(0); i < position.length(); i++) {
        if (position[i] + speed[i] > cubeLength) {
            position[i] = cubeLength;
            speed[i] = -(speed[i] + position[i] - cubeLength);
        } else if (position[i] + speed[i] < -cubeLength) {
            position[i] = -cubeLength;
            speed[i] = -(cubeLength + speed[i] + position[i]);
        } else {
            position[i] += speed[i];
        }
    }
}