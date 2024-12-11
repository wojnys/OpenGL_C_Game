#include "TextureModel.h"

TextureModel::TextureModel(const float points[], size_t size, GLenum shapeType, int first, int count)
    : shapeType(shapeType), first(first), count(count) {

    // Generate and bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

    // Enable vertex attributes
    glEnableVertexAttribArray(0); // Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);

    glEnableVertexAttribArray(1); // Colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

    glEnableVertexAttribArray(2); // Texture Coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));

    // Unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

TextureModel::~TextureModel() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void TextureModel::bind() {
    glBindVertexArray(VAO);
}

void TextureModel::unbind() {
    glBindVertexArray(0);
}

GLenum TextureModel::getShapeType() const {
    return shapeType;
}

int TextureModel::getFirst() const {
    return first;
}

int TextureModel::getCount() const {
    return count;
}


