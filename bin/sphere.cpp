#include "sphere.h"

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

Sphere::Sphere(glm::vec3 position, GLfloat radius, GLint countStacks, GLint countSectors) {
    this->position = position;
    this->setRadius(radius);
    this->setCountStacks(countStacks);
    this->setCountSectors(countSectors);
}

void Sphere::create() {
    GLfloat pi = glm::pi<GLfloat>();
    GLfloat stepStackAngle = pi / ((GLfloat) countStacks);
    GLfloat stepSectorAngle = 2 * pi / ((GLfloat) countSectors);
    GLfloat x, y, z;

    // Its easier to imagine that columns = countStacks, rows = countSectors
    // Or longitude = countStacks, latitude = countSectors

    for (int i(0); i < countStacks + 1; i++) {

        x = position.x + getRadius() * sin(stepStackAngle * i);
        y = position.y + getRadius() * cos(stepStackAngle * i);
        z = position.z;

        vectorVert.push_back(x); // == [size - 3]
        vectorVert.push_back(y); // == [size - 2]
        vectorVert.push_back(z); // == [size - 1]

        if (i == 0)
            continue;
            
        int size = vectorVert.size();   
        int countPoints =  size / 3;
        GLfloat circle_r = vectorVert[size - 3] - position.x;
        GLfloat circle_y = vectorVert[size - 2] - position.y;

        for (int j(1); j < countSectors; j++) {

            if  (i != countStacks) {
                x = position.x + circle_r * cos(stepSectorAngle * j);
                y = position.y + circle_y;
                z = position.z + circle_r * sin(stepSectorAngle * j);

                vectorVert.push_back(x);
                vectorVert.push_back(y);
                vectorVert.push_back(z);

                size = vectorVert.size();   
                countPoints = size / 3;
            }

            size = vectorVert.size();
            int lastElemntIndex = countPoints - 1;

            if (i == 1) {
                // If it is the "top" point

                indexes.push_back(0);
                indexes.push_back(j);
                indexes.push_back(j + 1);

                if (j == countSectors - 1) {
                    indexes.push_back(0);
                    indexes.push_back(lastElemntIndex);
                    indexes.push_back(i);
                }
            } else if (i == countStacks) {
                // If it is the "bottom" point

                indexes.push_back(lastElemntIndex);
                indexes.push_back(lastElemntIndex - j);
                indexes.push_back(lastElemntIndex - j - 1);
                if (j == countSectors - 1) {
                    indexes.push_back(lastElemntIndex);
                    indexes.push_back(lastElemntIndex - countSectors);
                    indexes.push_back(lastElemntIndex - 1);
                }
            } else {
                // If it is the "middle" point

                indexes.push_back(lastElemntIndex);
                indexes.push_back(lastElemntIndex - 1);
                indexes.push_back((lastElemntIndex) - countSectors - 1);

                indexes.push_back(lastElemntIndex);
                indexes.push_back(lastElemntIndex - countSectors);
                indexes.push_back(lastElemntIndex - countSectors - 1);

                if (j == countSectors - 1) {
                    // @TODO Beautiful triangles' lines

                    indexes.push_back(lastElemntIndex);
                    indexes.push_back(lastElemntIndex - countSectors + 1);
                    indexes.push_back(lastElemntIndex - 2 * countSectors + 1);

                    indexes.push_back(lastElemntIndex);
                    indexes.push_back(lastElemntIndex - countSectors);
                    indexes.push_back(lastElemntIndex - 2 * countSectors + 1);
                }
            }
        }
    }
    
    /// DEBUG ///

    // cout << endl << "VertSize: " << vectorVert.size() << endl;
    // cout << "IndexesSize: " << indexes.size() << endl;

    // for (int i(0); i < indexes.size(); i += 3) {
    //     cout << indexes[i] << ",   " << indexes[i + 1] << ",   " << indexes[i + 2] << ",   " << endl;
    // }

    // cout << endl << endl;

    // for (int i(0); i < vectorVert.size(); i += 3) {
    //     cout << vectorVert[i] << ",   " << vectorVert[i + 1] << ",   " << vectorVert[i + 2] << ",   " << endl;
    // }

    /// DEBUG ///
}

void Sphere::setBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vectorVert.size() * sizeof(GLfloat), &vectorVert[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(GLuint), &indexes[0], GL_STATIC_DRAW);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
                glEnableVertexAttribArray(0);
            //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);  
    glBindVertexArray(0);
}

void Sphere::draw(Shader shader, double time, int mode) {
    glBindVertexArray(VAO);
        glUniform4f(glGetUniformLocation(shader.program, "currentColor"), sin(time), 0.5f, 1.0f, 1.0f);
        if (mode)
            glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, 0);
        else
            glDrawElements(GL_LINE_LOOP, indexes.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}