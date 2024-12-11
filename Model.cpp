#include "Models.h"

Model::Model(const float points[], size_t size, GLenum shapeType, int first, int count) : shapeType(shapeType), first(first), count(count) {  // it is same like 	//this->shaderProgram = shaderProgram;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Model::~Model() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Model::bind() {
    glBindVertexArray(VAO);
}

void Model::unbind() {
    glBindVertexArray(0);
}

GLenum Model::getShapeType() const {
    return shapeType;
}
int Model::getFirst() const {
    return first;
}
int Model::getCount() const {
    return count;
}
