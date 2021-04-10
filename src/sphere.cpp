#include "sphere.h"

GLfloat Sphere::getRadius() {
    return this->radius;
}

GLuint Sphere::getCountStacks() {
    return this->countStacks;
}

GLuint Sphere::getCountSectors() { 
    return this->countSectors;
}

void Sphere::setRadius(GLfloat radius) {
    this->radius = radius;
}

void Sphere::setCountStacks(GLuint countStacks) {
    this->countStacks = countStacks;
}

void Sphere::setCountSectors(GLuint countSectors) {
    this->countSectors = countSectors;
}

/*! @brief Sets the values of object.
 *
 *  This function sets the values of object.
 * 
 *  @param[in] mass The mass in [kg] of object. 
 *  @param[in] radius The radius of object. 
 *  @param[in] countStacks The count of vertical lines of the object.
 *  @param[in] countSectors The count of horizontal lines of the object.
 *  @param[in] position The position of object.
 *  @param[in] speed The speed of object.
 *
 */
Sphere::Sphere(GLfloat mass, GLfloat radius, GLuint countStacks, GLuint countSectors, glm::vec3 position, glm::vec3 speed) {
    this->mass = mass;
    this->position = position;
    this->speed = speed;
    this->setRadius(radius);
    this->setCountStacks(countStacks);
    this->setCountSectors(countSectors);

    this->create();
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

        vectorVertices.push_back(x); // == [size - 3]
        vectorVertices.push_back(y); // == [size - 2]
        vectorVertices.push_back(z); // == [size - 1]

        if (i == 0)
            continue;
            
        int size = vectorVertices.size();   
        int countPoints =  size / 3;
        GLfloat circle_r = vectorVertices[size - 3] - position.x;
        GLfloat circle_y = vectorVertices[size - 2] - position.y;

        for (int j(1); j < countSectors; j++) {

            if  (i != countStacks) {
                x = position.x + circle_r * cos(stepSectorAngle * j);
                y = position.y + circle_y;
                z = position.z + circle_r * sin(stepSectorAngle * j);

                vectorVertices.push_back(x);
                vectorVertices.push_back(y);
                vectorVertices.push_back(z);

                size = vectorVertices.size();   
                countPoints = size / 3;
            }

            size = vectorVertices.size();
            int lastElemntIndex = countPoints - 1;

            if (i == 1) {
                // If it is the "top" point

                vectorIndexes.push_back(0);
                vectorIndexes.push_back(j);
                vectorIndexes.push_back(j + 1);

                if (j == countSectors - 1) {
                    vectorIndexes.push_back(0);
                    vectorIndexes.push_back(lastElemntIndex);
                    vectorIndexes.push_back(i);
                }
            } else if (i == countStacks) {
                // If it is the "bottom" point

                vectorIndexes.push_back(lastElemntIndex);
                vectorIndexes.push_back(lastElemntIndex - j);
                vectorIndexes.push_back(lastElemntIndex - j - 1);
                if (j == countSectors - 1) {
                    vectorIndexes.push_back(lastElemntIndex);
                    vectorIndexes.push_back(lastElemntIndex - countSectors);
                    vectorIndexes.push_back(lastElemntIndex - 1);
                }
            } else {
                // If it is the "middle" point

                vectorIndexes.push_back(lastElemntIndex);
                vectorIndexes.push_back(lastElemntIndex - 1);
                vectorIndexes.push_back((lastElemntIndex) - countSectors - 1);

                vectorIndexes.push_back(lastElemntIndex);
                vectorIndexes.push_back(lastElemntIndex - countSectors);
                vectorIndexes.push_back(lastElemntIndex - countSectors - 1);

                if (j == countSectors - 1) {
                    // @TODO Beautiful triangles' lines

                    vectorIndexes.push_back(lastElemntIndex);
                    vectorIndexes.push_back(lastElemntIndex - countSectors + 1);
                    vectorIndexes.push_back(lastElemntIndex - 2 * countSectors + 1);

                    vectorIndexes.push_back(lastElemntIndex);
                    vectorIndexes.push_back(lastElemntIndex - countSectors);
                    vectorIndexes.push_back(lastElemntIndex - 2 * countSectors + 1);
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


void Sphere::setBuffers(GLuint &VAO, GLuint &VBO, GLuint &EBO) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
                glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void Sphere::draw(GLuint &VAO, GLuint &VBO, GLuint &EBO, Shader &shader, vector<GLfloat> &vertData, vector<GLuint> &indexData, glm::vec4 color, int mode) {
    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertData.size() * sizeof(GLfloat), &vertData[0], GL_STREAM_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(GLuint), &indexData[0], GL_STREAM_DRAW);
                glUniform4fv(glGetUniformLocation(shader.program, "currentColor"), 1, glm::value_ptr(color));
                glDrawElements(mode, indexData.size(), GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Sphere::addDataTo(vector<GLfloat> &vertData, vector<GLuint> &indexData) {
    vertData.insert(vertData.end(), vectorVertices.begin(), vectorVertices.end());
    indexData.insert(indexData.end(), vectorIndexes.begin(), vectorIndexes.end());

    for (int i(indexData.size() - 1); i > indexData.size() - vectorIndexes.size() - 1; i--) {
        indexData[i] += (vertData.size() - vectorVertices.size()) / 3;
    }
}

void Sphere::move(GLfloat cubeLength) {
    for (int i(0); i < position.length(); i++) {
        if (position[i] + speed[i] > cubeLength) {
            changePosition(cubeLength, i);
            speed[i] = -(speed[i] + position[i] - cubeLength);
        } else if (position[i] + speed[i] < -cubeLength) {
            changePosition(-cubeLength, i);
            speed[i] = -(cubeLength + speed[i] + position[i]);
        } else {
            changePosition(position[i] + speed[i], i);
        }
    }
}

void Sphere::changePosition(GLfloat newCoord, GLuint index) {
    for (int i(index); i < vectorVertices.size(); i += 3) {
        vectorVertices[i] += newCoord - position[index];
    }
    position[index] = newCoord;
}