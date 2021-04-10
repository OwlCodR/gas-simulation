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
        GLfloat rand_x_speed = (GLfloat) (rand() % 200 - 100) / 10000.0f * cubeLength;
        GLfloat rand_y_speed = (GLfloat) (rand() % 200 - 100) / 10000.0f * cubeLength;
        GLfloat rand_z_speed = (GLfloat) (rand() % 200 - 100) / 10000.0f * cubeLength;

        glm::vec3 pos(rand_x_pos, rand_y_pos, rand_z_pos);
        glm::vec3 speed(rand_x_speed, rand_y_speed, rand_z_speed);

        //cout << "\n" << glm::to_string(pos) << " " << glm::to_string(speed) << endl;
        //cout << "\n" << glm::length(speed) / 0.015f << endl;

        objects.push_back(T(0.000005f, 0.01f, 20, 20, pos, speed));

        objects[i].addDataTo(vertData, indexData);
    }
}

template <class T>
void Simulation<T>::moveObjects() {
    for (int i(0); i < objects.size(); i++) {
        objects[i].move(cubeLength);
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

    //GLfloat x = (position1.x - position2.x) / (speed2.x - speed1.x);
    //GLfloat y = (position1.y - position2.y) / (speed2.y - speed1.y);
    //GLfloat x = (position1.z - position2.z) / (speed2.z - speed1.z);
    return false;
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
    // May be better to change data, not to set always new
    vertData.clear();
    indexData.clear();
    for (int i(0); i < objects.size(); i++) {
        objects[i].addDataTo(vertData, indexData);

        // vertData.push_back(objects[i].position.x);
        // vertData.push_back(objects[i].position.y);
        // vertData.push_back(objects[i].position.z);

        // vertData.push_back(objects[i].speed.x);
        // vertData.push_back(objects[i].speed.y);
        // vertData.push_back(objects[i].speed.z);
    }

    //debug

    // for (int i(0); i < vertData.size(); i++) {
    //     cout << vertData[i] << endl;
    // }
}

template <class T>
void Simulation<T>::setBuffers() {
    T::setBuffers(VAO, VBO, EBO);
}

template <class T>
void Simulation<T>::draw(Shader shader, glm::vec4 color) {
    T::draw(VAO, VBO, EBO, shader, vertData, indexData, color, GL_TRIANGLES);
    // glBindVertexArray(VAO);
    //     glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //         glBufferData(GL_ARRAY_BUFFER, vertData.size() * sizeof(GLfloat), &vertData[0], GL_STREAM_DRAW);
    //         //glUniform4fv(glGetUniformLocation(shader.program, "currentColor"), 1, glm::value_ptr(color));
    //     glDrawArrays(GL_POINTS, 0, vertData.size() / 6);
    // glBindVertexArray(0);
}
