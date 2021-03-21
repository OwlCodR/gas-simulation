#include "particle.h"

Particle::Particle(glm::vec3 position, glm::vec3 direction) {
    this->position = position;
    this->direction = direction;
}

void Particle::move(GLfloat MAX_POS) {
    for (int i(0); i < position.length(); i++) {
        if (position[i] + direction[i] > MAX_POS) {
            position[i] = MAX_POS;
            direction[i] = -(direction[i] + position[i] - MAX_POS);
        } else if (position[i] + direction[i] < -MAX_POS) {
            position[i] = -MAX_POS;
            direction[i] = -(MAX_POS + direction[i] + position[i]);
        } else {
            position[i] += direction[i];
        }
    }
}