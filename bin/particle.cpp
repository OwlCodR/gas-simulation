#include "particle.h"

Particle::Particle(glm::vec2 position, glm::vec2 direction) {
    this->position = position;
    this->direction = direction;
}

void Particle::move(GLfloat MAX_POS) {
    if (position.x + direction.x > MAX_POS) {
        position.x = MAX_POS;
        direction.x = -(direction.x + position.x - MAX_POS);
    } else if (position.x + direction.x < -MAX_POS) {
        position.x = -MAX_POS;
        direction.x = -(MAX_POS + direction.x + position.x);
    } else {
        position.x += direction.x;
    }

    if (position.y + direction.y > MAX_POS) {
        position.y = MAX_POS;
        direction.y = -(direction.y + position.y - MAX_POS);
    } else if (position.y + direction.y < -MAX_POS) {
        position.y = -MAX_POS;
        direction.y = -(MAX_POS + direction.y + position.y);
    } else {
        position.y += direction.y;
    }
}