#ifndef CYLINDER_H
#define CYLINDER_H

#include "object3d.h"

using namespace std;

class Cylinder : Object3D {
private:
    GLfloat radius;
    GLfloat height;
    GLuint countSectors;
public: 
    Cylinder(glm::vec3 position, GLfloat radius, GLfloat height, GLuint countSectors);

    GLfloat getRadius();
    GLfloat getHeight();
    GLuint getCountSectors();

    void setRadius(GLfloat radius);
    void setHeight(GLfloat height);
    void setCountSectors(GLuint countSectors);

    void create() override;
    void setBuffers() override;
    void draw(Shader shader, glm::vec4 color, int mode) override;
};

#endif