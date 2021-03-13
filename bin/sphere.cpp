#include "sphere.h"

/*
Square::Square(vector<glm::vec3> vectorPoints) {
    setVectorPoints(vectorPoints);
}

vector<glm::vec3> Square::getVectorPoints() {
    return this->vectorPoints;
}

void Square::setVectorPoints(vector<glm::vec3> vectorPoints) {
    this->vectorPoints = vectorPoints; 
}
*/
////

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

Sphere::Sphere(GLfloat radius, GLint countStacks, GLint countSectors) {
    this->setRadius(radius);
    this->setCountStacks(countStacks);
    this->setCountSectors(countSectors);
}

void Sphere::create() {
    GLfloat pi = glm::pi<GLfloat>();
    GLfloat stepStackAngle = pi / ((GLfloat) countStacks);
    GLfloat stepSectorAngle = 2 * pi / ((GLfloat) countSectors);
    // cout << stepStackAngle << " " << stepSectorAngle << endl;
    GLfloat x, y, z;

    for (int i(0); i < countStacks + 1; i++) {
        x = 0.0f + getRadius() * sin(stepStackAngle * i);
        y = 0.0f + getRadius() * cos(stepStackAngle * i);
        z = 0.0f;
        vectorVert.push_back(x); // [size - 3]
        vectorVert.push_back(y); // [size - 2]
        vectorVert.push_back(z); // [size - 1]

        // cout << endl << "stack: " << x << " " << y << " " << z << endl;

        if (i == 0)
            continue;
            
        int size = vectorVert.size();   
        int countPoints =  size / 3;
        GLfloat stack_x = vectorVert[size - 3];
        GLfloat stack_y = vectorVert[size - 2];
        GLfloat stack_z = vectorVert[size - 1];

        for (int j(1); j < countSectors; j++) {

            if  (i != countStacks) {
                

                x = stack_x * cos(stepSectorAngle * j);
                y = stack_y;
                z = stack_x * sin(stepSectorAngle * j);

                vectorVert.push_back(x);
                vectorVert.push_back(y);
                vectorVert.push_back(z);

                size = vectorVert.size();   
                countPoints =  size / 3;
            }

            //indexes.push_back(i);
            //indexes.push_back(i);

            // cout << endl << "sector: " << x << " " << y << " " << z << endl;

            //////////////////
            size = vectorVert.size(); 
            if (i == 1) {
                indexes.push_back(0);
                indexes.push_back(j);
                indexes.push_back(j + 1);

                if (j == countSectors - 1) {
                    indexes.push_back(0);
                    indexes.push_back(countPoints - 1); // last element
                    indexes.push_back(i);
                }
            } else if (i == countStacks) {
                indexes.push_back(countPoints - 1);
                indexes.push_back(countPoints - j - 1);
                indexes.push_back(countPoints - j - 2);
                if (j == countSectors - 1) {
                    indexes.push_back(countPoints - 1);
                    indexes.push_back((countPoints - 1) - countSectors); // last element
                    cout << (countPoints - 1) - countSectors;
                    indexes.push_back(countPoints - 2);
                }
            } else {
                indexes.push_back(countPoints - 1);
                indexes.push_back(countPoints - 2);
                indexes.push_back((countPoints - 1) - countSectors - 1);

                indexes.push_back(countPoints - 1);
                indexes.push_back((countPoints - 1) - countSectors);
                indexes.push_back((countPoints - 1) - countSectors - 1);

                // cout << "Added main 2 triangles\n";

                if (j == countSectors - 1) {
                    indexes.push_back(countPoints - 1);
                    indexes.push_back((countPoints - 1) - countSectors + 1);
                    indexes.push_back((countPoints - 1) - 2 * countSectors + 1);

                    indexes.push_back(countPoints - 1);
                    indexes.push_back((countPoints - 1) - countSectors);
                    indexes.push_back(countPoints - 2 * countSectors);

                    // cout << "Added 2 more triangles - " << countPoints - 1 << "\n";
                }
            }
        }

        //cout << endl << stepStackAngle * i << " " << sin(stepStackAngle * i) << " " << cos(stepStackAngle * i) << endl;
        
    }
    
    cout << endl << "VertSize: " << vectorVert.size() << endl;
    cout << "IndexesSize: " << indexes.size() << endl;

    for (int i(0); i < indexes.size(); i += 3) {
        cout << indexes[i] << ",   " << indexes[i + 1] << ",   " << indexes[i + 2] << ",   " << endl;
        //cout << "i = " << i << endl;
    }

    cout << endl << endl;

    for (int i(0); i < vectorVert.size(); i += 3) {
        cout << vectorVert[i] << ",   " << vectorVert[i + 1] << ",   " << vectorVert[i + 2] << ",   " << endl;
    }
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
