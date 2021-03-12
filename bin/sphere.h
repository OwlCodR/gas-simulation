#ifndef SPHERE_H
#define SPHERE_H

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

/*
class Square {
private:
    vector<glm::vec3> vectorPoints;
public:
    Square(vector<glm::vec3> vectorPoints);
    vector<glm::vec3> getVectorPoints();
    void setVectorPoints(vector<glm::vec3> vectorPoints);
};
*/

class Sphere
{
public:
    vector<GLfloat> vectorVert; // Every Stack contains vectorSectors
    Sphere(GLfloat radius, GLint countStacks, GLint countSectors);

    GLfloat getRadius();
    GLint getCountStacks();
    GLint getCountSectors();

    void setRadius(GLfloat radius);
    void setCountStacks(GLint countStacks);
    void setCountSectors(GLint countSectors);
private:
    GLfloat radius;
    GLint countStacks;
    GLint countSectors;
    void create();
    void draw();
};



#endif