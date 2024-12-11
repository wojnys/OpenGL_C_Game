
#pragma once


#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Subject.h"


class Light : public Subject {
public:
    void setPosition(const glm::vec3& position) {
        lightPosition = position;
        this->notify(EventType::Light, this);
    }

    void setColor(const glm::vec4& color) {
        lightColor = color;
        this->notify(EventType::Light, this);
    }

    glm::vec3 getPosition() const {
        return lightPosition;
    }

    glm::vec4 getColor() const {
        return lightColor;
    }

private:
    glm::vec3 lightPosition;
    glm::vec4 lightColor;
};