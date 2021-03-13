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

class Sphere
{
public:
    static const int LINE = 0;
    static const int FILL = 1;

    vector<GLfloat> vectorVert; 
    vector<GLuint> indexes; 
    Sphere(GLfloat radius, GLint countStacks, GLint countSectors);

    GLfloat getRadius();
    GLint getCountStacks();
    GLint getCountSectors();

    void setRadius(GLfloat radius);
    void setCountStacks(GLint countStacks);
    void setCountSectors(GLint countSectors);

    void create();
    void setBuffers();
    void draw(Shader shader, double time, int mode);
private:
    GLuint EBO, VBO, VAO;
    GLfloat radius;
    GLint countStacks;
    GLint countSectors;
};

#endif