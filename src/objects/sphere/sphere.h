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

#include "../object.h"

using namespace std;

class Sphere : public Object {
public:
    vector<GLfloat> vectorVertices;
    vector<GLuint> vectorIndexes;
    
    Sphere(GLfloat mass, GLfloat radius, GLuint countStacks, GLuint countSectors, glm::vec3 position, glm::vec3 speed);

    GLfloat getRadius();
    GLuint getCountStacks();
    GLuint getCountSectors();

    void setRadius(GLfloat radius);
    void setCountStacks(GLuint countStacks);
    void setCountSectors(GLuint countSectors);

    void addDataTo(vector<GLfloat> &vertData, vector<GLuint> &indexData);
    void move(GLfloat cubeLength) override;

    static void setBuffers(GLuint &VAO, GLuint &VBO, GLuint &EBO);
    static void draw(GLuint &VAO, GLuint &VBO, GLuint &EBO, Shader &shader, vector<GLfloat> &vertData, vector<GLuint> &indexes, glm::vec4 color, int mode);
private:
    GLuint index;
    GLuint countStacks;
    GLuint countSectors;

    void changePosition(GLfloat newCoord, GLuint index);
    void create();
};

#endif