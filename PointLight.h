#pragma once

#include "LightInterface.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "EventType.h"

class PointLight : public LightInterface
{
public:
    PointLight(glm::vec3 lightPosition, glm::vec4 lightColor, float intensity)
        : lightPosition(lightPosition), lightColor(lightColor), intensity(intensity) {}

    void setPosition(glm::vec3 lightPosition) override {
        this->lightPosition = lightPosition;
        this->notify(EventType::PointLight, this);
    }

    void setColor(glm::vec4 lightColor) override {
        this->lightColor = lightColor;
        this->notify(EventType::PointLight, this);
    }

    void setIntensity(float intensity) override {
        this->intensity = intensity;
        this->notify(EventType::PointLight, this);
    }

    glm::vec3 getPosition() const override {
        return lightPosition;
    }
    glm::vec4 getColor() const override {
        return lightColor;
    }
    float getIntensity() const override {
        return intensity;
    }

    EventType getType() const override { return EventType::PointLight; }

private:
    glm::vec3 lightPosition;
    glm::vec4 lightColor;
    float intensity;
};



