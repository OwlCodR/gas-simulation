#include "sphere.h"

/*
Square::Square(vector<glm::vec3> vectorPoints) {
    setVectorPoints(vectorPoints);
}

vector<glm::vec3> Square::getVectorPoints() {
    return this->vectorPoints;
}

void Square::setVectorPoints(vector<glm::vec3> vectorPoints) {
    this->vectorPoints = vectorPoints; 
}
*/
////

GLfloat Sphere::getRadius() {
    return this->radius;
}

GLint Sphere::getCountStacks() {
    return this->countStacks;
}

GLint Sphere::getCountSectors() { 
    return this->countSectors;
}

void Sphere::setRadius(GLfloat radius) {
    this->radius = radius;
}

void Sphere::setCountStacks(GLint countStacks) {
    this->countStacks = countStacks;
}

void Sphere::setCountSectors(GLint countSectors) {
    this->countSectors = countSectors;
}

Sphere::Sphere(GLfloat radius, GLint countStacks, GLint countSectors) {
    this->setRadius(radius);
    this->setCountStacks(countStacks);
    this->setCountSectors(countSectors);
}

void Sphere::create() {
    GLfloat stepStackAngle = ((GLfloat) (180)) / ((GLfloat) countStacks);
    GLfloat stepSectorAngle = ((GLfloat) (360)) / ((GLfloat) countSectors);
    GLfloat x, y, z;
    
    for (int k(0); k < countSectors; k++) {
        x = 0.0f + getRadius() * cos(stepSectorAngle * k);
        z = 0.0f + getRadius() * sin(stepStackAngle * k);
    }

    for (int i(0); i < countStacks; i++) {
        x = 0.0f + getRadius() * sin(stepStackAngle * i);
        y = 0.0f + getRadius() * cos(stepStackAngle * i);
        z = 0.0f;
        vectorVert.push_back(x);
        vectorVert.push_back(y);
        vectorVert.push_back(z);
    }
}