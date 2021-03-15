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
    vector<GLfloat> vectorVert;
    vector<GLuint> indexes;
    glm::vec3 position;
    
    Sphere(glm::vec3 position, GLfloat radius, GLuint countStacks, GLuint countSectors);

    GLfloat getRadius();
    GLuint getCountStacks();
    GLuint getCountSectors();

    void setRadius(GLfloat radius);
    void setCountStacks(GLuint countStacks);
    void setCountSectors(GLuint countSectors);

    void create();
    void setBuffers();
    void draw(Shader shader, glm::vec4 color, int mode);
private:
    GLuint EBO, VBO, VAO;
    GLfloat radius;
    GLuint countStacks;
    GLuint countSectors;
};

#endif