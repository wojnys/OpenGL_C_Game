#pragma once

#include "Subject.h"
#include "DrawableObject.h"
#include <glm/glm.hpp>
#include <GL/glew.h>


class LightInterface : public Subject {
public:
    virtual void setPosition(glm::vec3 lightPosition) = 0;
    virtual void setColor(glm::vec4 lightColor) = 0;
    virtual void setIntensity(float intensity) = 0;
    virtual glm::vec3 getPosition() const = 0;
    virtual glm::vec4 getColor() const = 0;
    virtual float getIntensity() const = 0;

    virtual EventType getType() const = 0;

    virtual ~LightInterface() = default;
};


