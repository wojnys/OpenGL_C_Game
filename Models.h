#pragma once

#include "ShaderProgram.h"
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CompositeTransformation.h"
#include "ModelBase.h"

class Model: public ModelBase {
public:
    Model(const float points[], size_t size, GLenum shapeType, int first, int count );
    ~Model();
    void bind();
    void unbind();

	GLenum getShapeType() const;
	int getFirst() const;
    int getCount() const;

private:
    GLuint VBO, VAO;

	GLenum shapeType;
	int first;
	int count;
};