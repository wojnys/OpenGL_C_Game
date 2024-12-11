#pragma once
#include <GL/glew.h>

class ModelBase {
public:
    virtual ~ModelBase() = default;

    virtual void bind() = 0;
    virtual void unbind() = 0;

    virtual GLenum getShapeType() const = 0;

    virtual int getFirst() const = 0;
    virtual int getCount() const = 0;
};





