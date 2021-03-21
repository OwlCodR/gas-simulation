#include "simulation.h"

template <class T>
Simulation<T>::Simulation(GLuint count) {
    this->count = count;
}

template <class T>
void Simulation<T>::create() {
    srand(time(NULL));
    // for (int i(0); i < 100; i++)
    //     cout << "\n" << (GLfloat) (rand() % (2 * MAX_POS)) << endl;
    for (int i(0); i < count; i++) {
        // random [-MAX_POS; MAX_POS]
        // ...*100.0/100.0 Because rand() can't generate float values
        GLfloat rand_x_pos = (GLfloat) (rand() % (2 * MAX_POS * 100) + 1 - MAX_POS * 100.0f) / 100.0f;
        GLfloat rand_y_pos = (GLfloat) (rand() % (2 * MAX_POS * 100) + 1 - MAX_POS * 100.0f) / 100.0f;
        GLfloat rand_z_pos = (GLfloat) (rand() % (2 * MAX_POS * 100) + 1 - MAX_POS * 100.0f) / 100.0f;

        // random [-MAX_POS / 2; MAX_POS / 2]
        GLfloat rand_x_dir = (GLfloat) (rand() % 200 - 100) / 10000.0f;
        GLfloat rand_y_dir = (GLfloat) (rand() % 200 - 100) / 10000.0f;
        GLfloat rand_z_dir = (GLfloat) (rand() % 200 - 100) / 10000.0f;

        glm::vec3 pos(rand_x_pos, rand_y_pos, rand_z_pos);
        glm::vec3 dir(rand_x_dir, rand_y_dir, rand_z_dir);

        // cout << "\n" << glm::to_string(pos) << " " << glm::to_string(dir) << endl;
        //cout << "\n" << glm::length(dir) / 0.015f << endl;

        objects.push_back(T(pos, dir));

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
    data.clear();
    for (int i(0); i < objects.size(); i++) {
        objects[i].move(MAX_POS);
        data.push_back(objects[i].position.x);
        data.push_back(objects[i].position.y);
        data.push_back(objects[i].position.z);

        data.push_back(objects[i].direction.x);
        data.push_back(objects[i].direction.y);
        data.push_back(objects[i].direction.z);
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
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
                glEnableVertexAttribArray(0);
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
