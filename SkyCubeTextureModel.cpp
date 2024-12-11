#include "SkyCubeTextureModel.h"

//SkyCubeTextureModel::SkyCubeTextureModel(const float points[], size_t size, GLenum shapeType, int first, int count)
//    : shapeType(shapeType), first(first), count(count) {
//
//    //Vertex Array Object (VAO)
//    GLuint VBO = 0;
//    glGenBuffers(1, &VBO); // generate the VBO
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points[0], GL_STATIC_DRAW);
//
//    GLuint VAO = 0;
//    glGenVertexArrays(1, &VAO); //generate the VAO
//    glBindVertexArray(VAO); //bind the VAO
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//    //enable vertex attributes
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
//}
//
//SkyCubeTextureModel::~SkyCubeTextureModel() {
//    glDeleteBuffers(1, &VBO);
//    glDeleteVertexArrays(1, &VAO);
//}
//
//void SkyCubeTextureModel::bind() {
//    glBindVertexArray(VAO);
//}
//
//void SkyCubeTextureModel::unbind() {
//    glBindVertexArray(0);
//}
//
//GLenum SkyCubeTextureModel::getShapeType() const {
//    return shapeType;
//}
//
//int SkyCubeTextureModel::getFirst() const {
//    return first;
//}
//
//int SkyCubeTextureModel::getCount() const {
//    return count;
//}



#include "SkyCubeTextureModel.h"

SkyCubeTextureModel::SkyCubeTextureModel(const float points[], size_t size, GLenum shapeType, int first, int count)
    : shapeType(shapeType), first(first), count(count) {

    // Store the VAO and VBO as member variables
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind VBO and upload data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

    // Enable and configure vertex attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);

    // Unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

SkyCubeTextureModel::~SkyCubeTextureModel() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void SkyCubeTextureModel::bind() {
    glBindVertexArray(VAO);
}

void SkyCubeTextureModel::unbind() {
    glBindVertexArray(0);
}

GLenum SkyCubeTextureModel::getShapeType() const {
    return shapeType;
}

int SkyCubeTextureModel::getFirst() const {
    return first;
}

int SkyCubeTextureModel::getCount() const {
    return count;
}