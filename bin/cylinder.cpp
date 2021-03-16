#include "cylinder.h"

void Cylinder::setRadius(GLfloat radius) {
    this->radius = radius;
}

GLfloat Cylinder::getRadius() {
    return this->radius;
}

void Cylinder::setHeight(GLfloat height) {
    this->height = height;
}

GLfloat Cylinder::getHeight() {
    return this->height;
}

void Cylinder::setCountSectors(GLuint countSectors) {
    this->countSectors = countSectors;
}

GLuint Cylinder::getCountSectors() {
    return this->countSectors;
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
Cylinder::Cylinder(glm::vec3 position, GLfloat radius, GLfloat height, GLuint countSectors) {
    setPosition(position);
    setRadius(radius);
    setHeight(height);
    setCountSectors(countSectors);
}

/*! @brief Creates object.
 *
 *  This function creates the vector<GLfloat> of coordinates points of object.
 * 
 *  @param[in] shader The Shader where is the "currentColor" variable.
 *  @param[in] color The color of object.
 *  @param[in] mode The mode of drawing. GL_TRIANGLES or GL_LINE_LOOP for example.
 *
*/
void Cylinder::create() {
    GLfloat angle = 2 * glm::pi<GLfloat>() / (GLfloat) getCountSectors();
    GLfloat x, y, z;

    getVertices().push_back(getPosition().x);
    getVertices().push_back(getPosition().y + getHeight() / 2.0f);
    getVertices().push_back(getPosition().z);

    for (int i(0); i < 2 + 1; i++) {
        for (int j(0); j < getCountSectors(); j++) {

            if (i != 2) {
                x = getPosition().x + getRadius() * cos(angle * j);

                if (i == 0)
                    y = getPosition().y + getHeight() / 2.0f ;
                else 
                    y = getPosition().y - getHeight() / 2.0f ;

                z = getPosition().z + getRadius() * sin(angle * j);

                getVertices().push_back(x);
                getVertices().push_back(y);
                getVertices().push_back(z);
            }

            if (j == 0)
                continue;

            int currentIndex = (getCountSectors() * i + 1) + j;
            if (i == 0) {
                // Top
                getIndexes().push_back(i);
                getIndexes().push_back(i + j + 1);
                getIndexes().push_back(i + j);

                if (j == getCountSectors() - 1) {
                    // Extra triangles

                    getIndexes().push_back(i);
                    getIndexes().push_back(currentIndex);
                    getIndexes().push_back(currentIndex - j);
                }
            } else if (i == 2) {
                // Bottom
                if (j == 1) {
                    getVertices().push_back(getPosition().x);
                    getVertices().push_back(getPosition().y - getHeight() / 2.0f);
                    getVertices().push_back(getPosition().z);
                }

                getIndexes().push_back(getVertices().size() / 3 - 1);
                getIndexes().push_back(getCountSectors() + j + 1);
                getIndexes().push_back(getCountSectors() + j);

                if (j == getCountSectors() - 1) {
                    // Extra triangles

                    getIndexes().push_back(getVertices().size() / 3 - 1);
                    getIndexes().push_back(getCountSectors() + j + 1);
                    getIndexes().push_back(getCountSectors() * i + j - 2* getCountSectors() + 2);
                }
            } else {

                // Middle
                getIndexes().push_back(currentIndex);
                getIndexes().push_back(currentIndex - 1);
                getIndexes().push_back(currentIndex - 1 - getCountSectors());

                getIndexes().push_back(currentIndex);
                getIndexes().push_back(currentIndex - getCountSectors());
                getIndexes().push_back(currentIndex - getCountSectors() - 1);

                if (j == getCountSectors() - 1) {
                    // Extra triangles

                    getIndexes().push_back(currentIndex);
                    getIndexes().push_back(currentIndex - getCountSectors());
                    getIndexes().push_back(currentIndex - 2 * getCountSectors() + 1);

                    getIndexes().push_back(currentIndex);
                    getIndexes().push_back(currentIndex - getCountSectors() + 1);
                    getIndexes().push_back(currentIndex - 2 * getCountSectors() + 1);
                }
            }
        }
    }

    cout << endl;

    for (int i(0); i < getVertices().size(); i += 3) {
        cout << getVertices()[i] << ",   " << getVertices()[i + 1] << ",   " << getVertices()[i + 2] << ",   " << endl;
    }

    cout << "==\n";

    for (int i(0); i < getIndexes().size(); i += 3) {
        cout << getIndexes()[i] << ",   " << getIndexes()[i + 1] << ",   " << getIndexes()[i + 2] << ",   " << endl;
    }
}


/*! @brief Sets the buffers of object.
 *
 *  This function sets VBO buffer into VAO. It insert buffer data also.
 *
 */
void Cylinder::setBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, getVertices().size() * sizeof(GLfloat), &getVertices()[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, getIndexes().size() * sizeof(GLuint), &getIndexes()[0], GL_STATIC_DRAW);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
                glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

/*! @brief Draws the object using VAO and VBO
 *
 *  This function uses glDrawElements() to draw
 *  with draw-mode and sets the color of object
 *
 *  @param[in] shader The Shader where is the "currentColor" variable.
 *  @param[in] color The color of object.
 *  @param[in] mode The mode of drawing. GL_TRIANGLES or GL_LINE_LOOP for example.
 *
 */
void Cylinder::draw(Shader shader, glm::vec4 color, int mode) {
    glBindVertexArray(VAO);
        glUniform4fv(glGetUniformLocation(shader.program, "currentColor"), 1, glm::value_ptr(color));
        glDrawElements(mode, getIndexes().size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}