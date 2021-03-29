#include "simulation.h"

template <class T>
Simulation<T>::Simulation(GLfloat cubeLength, GLuint count) {
    this->cubeLength = cubeLength;
    this->count = count;
}

template <class T>
void Simulation<T>::create() {
    srand(time(NULL));
    // for (int i(0); i < 100; i++)
    //     cout << "\n" << (GLfloat) (rand() % (2 * cubeLength)) << endl;
    for (int i(0); i < count; i++) {
        // random [-cubeLength; cubeLength]
        // ...*100.0/100.0 Because rand() can't generate float values
        GLfloat rand_x_pos = (GLfloat) (rand() % 200 + 1 - 100.0f) / 100.0f * cubeLength;
        GLfloat rand_y_pos = (GLfloat) (rand() % 200 + 1 - 100.0f) / 100.0f * cubeLength;
        GLfloat rand_z_pos = (GLfloat) (rand() % 200 + 1 - 100.0f) / 100.0f * cubeLength;

        // random [-cubeLength / 2; cubeLength / 2]
        GLfloat rand_x_dir = (GLfloat) (rand() % 200 - 100) / 10000.0f * cubeLength;
        GLfloat rand_y_dir = (GLfloat) (rand() % 200 - 100) / 10000.0f * cubeLength;
        GLfloat rand_z_dir = (GLfloat) (rand() % 200 - 100) / 10000.0f * cubeLength;

        glm::vec3 pos(rand_x_pos, rand_y_pos, rand_z_pos);
        glm::vec3 dir(rand_x_dir, rand_y_dir, rand_z_dir);

        // cout << "\n" << glm::to_string(pos) << " " << glm::to_string(dir) << endl;
        // cout << "\n" << glm::length(dir) / 0.015f << endl;

        objects.push_back(T(0.0001f, 0.005f, pos, dir));

        data.push_back(rand_x_pos);
        data.push_back(rand_y_pos);
        data.push_back(rand_z_pos);

        data.push_back(rand_x_dir);
        data.push_back(rand_y_dir);
        data.push_back(rand_z_dir);
    }
}

template <class T>
void Simulation<T>::moveObjects() {
    // data.clear();
    for (int i(0); i < objects.size(); i++) {
        objects[i].move(cubeLength);
        // data.push_back(objects[i].position.x);
        // data.push_back(objects[i].position.y);
        // data.push_back(objects[i].position.z);

        // data.push_back(objects[i].speed.x);
        // data.push_back(objects[i].speed.y);
        // data.push_back(objects[i].speed.z);
    }
}

bool isRayCollision(glm::vec3 position1, glm::vec3 speed1, glm::vec3 position2, glm::vec3 speed2) {

    /* 
        position1 = vec3(x1, y1, z1)
        speed1 = vec3(v1) 
        a, b = some numbers

        There is rays collision if:
        position1 + a * speed1 = position2 + b * speed2

        1. x1 + a * v1.x = x2 + b * v2.x
        2. y1 + a * v1.y = y2 + b * v2.y
        3. z1 + a * v1.z = z2 + b * v2.z

        If a > 0 and b > 0 there is ray collision
    */

    GLfloat x = (position1.x - position2.x) / (speed2.x - speed1.x);
    GLfloat y = (position1.y - position2.y) / (speed2.y - speed1.y);
    GLfloat x = (position1.z - position2.z) / (speed2.z - speed1.z);
}

template <class T>
void Simulation<T>::checkCollisions() {
    for (int i(0); i < objects.size() - 1; i++) {
        for (int j(i + 1); j < objects.size(); j++) {
            if (glm::length(objects[i].position - objects[j].position) <= objects[i].radius + objects[j].radius) {
                glm::vec3 tmp = objects[i].speed;
                objects[i].speed = objects[j].speed;
                objects[j].speed = tmp;
            }
        }
    }
}

template <class T>
void Simulation<T>::setData() {
    data.clear();
    for (int i(0); i < objects.size(); i++) {
        data.push_back(objects[i].position.x);
        data.push_back(objects[i].position.y);
        data.push_back(objects[i].position.z);

        data.push_back(objects[i].speed.x);
        data.push_back(objects[i].speed.y);
        data.push_back(objects[i].speed.z);
    }
}

template <class T>
void Simulation<T>::setBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STREAM_DRAW);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) 0);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
                glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

template <class T>
void Simulation<T>::draw(Shader shader) {
    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STREAM_DRAW);
            //glUniform4fv(glGetUniformLocation(shader.program, "currentColor"), 1, glm::value_ptr(color));
        glDrawArrays(GL_POINTS, 0, data.size() / 6);
    glBindVertexArray(0);
}
