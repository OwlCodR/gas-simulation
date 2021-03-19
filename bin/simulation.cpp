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
        // ...*10.0/10.0 Because rand() can't generate float values
        GLfloat rand_x_pos = (GLfloat) (rand() % (2 * MAX_POS * 100) + 1 - MAX_POS * 100.0f) / 100.0f;
        GLfloat rand_y_pos = (GLfloat) (rand() % (2 * MAX_POS * 100) + 1 - MAX_POS * 100.0) / 100.0f;
        GLfloat rand_z_pos = (GLfloat) (rand() % (2 * MAX_POS * 100) + 1 - MAX_POS * 100.0) / 100.0f;

        // random [-MAX_POS / 2; MAX_POS / 2]
        GLfloat rand_x_dir = (GLfloat) (rand() % 10) / 1000.0f;
        GLfloat rand_y_dir = (GLfloat) (rand() % 10) / 1000.0f;

        glm::vec2 pos(rand_x_pos, rand_y_pos);
        glm::vec2 dir(rand_x_dir, rand_y_dir);

        //cout << "\n" << glm::to_string(pos) << " " << glm::to_string(dir) << endl;

        objects.push_back(T(pos, dir));

        vertices.push_back(rand_x_pos);
        vertices.push_back(rand_y_pos);
        vertices.push_back(rand_z_pos);
    }
}

template <class T>
void Simulation<T>::moveObjects() {
    vertices.clear();
    for (int i(0); i < objects.size(); i++) {
        objects[i].move(MAX_POS);
        vertices.push_back(objects[i].position.x);
        vertices.push_back(objects[i].position.y);
        //vertices.push_back(objects[i].position.x);
        // idk how it works
    }
}

template <class T>
void Simulation<T>::setBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STREAM_DRAW);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
                glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

template <class T>
void Simulation<T>::draw(Shader shader, glm::vec4 color) {
    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STREAM_DRAW);
        glUniform4fv(glGetUniformLocation(shader.program, "currentColor"), 1, glm::value_ptr(color));
        glDrawArrays(GL_POINTS, 0, vertices.size());
    glBindVertexArray(0);
}
