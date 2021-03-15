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
 *  @param[in] position The glm::vec3(x, y, z) of position of object. 
 *  @param[in] radius The GLfloat length of radius.
 *  @param[in] countStacks The GLint value which means how much horizontal lines will contain the object.
 *  @param[in] countSectors The GLint value which means how much vertical lines will contain the object.
 *
 */
Sphere::Sphere(glm::vec3 position, GLfloat radius, GLuint countStacks, GLuint countSectors) {
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


/*! @brief Sets the buffers of sphere.
 *
 *  This function sets VBO and EBO buffers into VAO. It insert buffer data also.
 *
 *  @ingroup sphere
 */
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
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

/*! @brief Draws the sphere using VAO and EBO
 *
 *  This function uses glDrawElements() to draw array of indexes (EBO)
 *  with draw-mode and sets the color of sphere
 *
 *  @param[in] shader The Shader where is the "currentColor" variable.
 *  @param[in] color The color of sphere.
 *  @param[in] mode The mode of drawing. GL_TRIANGLES or GL_LINE_LOOP for example.
 *
 *  @ingroup sphere
 */
void Sphere::draw(Shader shader, glm::vec4 color, int mode) {
    glBindVertexArray(VAO);
        glUniform4fv(glGetUniformLocation(shader.program, "currentColor"), 1, glm::value_ptr(color));
        glDrawElements(mode, indexes.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}