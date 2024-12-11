#pragma once
#pragma once

#include "LightInterface.h"
#include "Camera.h"

class DirectionLight : public LightInterface
{
public:
    DirectionLight(glm::vec3 direction, glm::vec4 lightColor)
        : direction(direction), lightColor(lightColor) {}

    // I dont need position in directional light
    void setPosition(glm::vec3 lightPosition) override {
    }

    void setColor(glm::vec4 lightColor) override {
        lightColor = lightColor;
        this->notify(EventType::SpotLight, this);
    }

    void setDirection(glm::vec3 direction) {
        direction = direction;
        this->notify(EventType::SpotLight, this);
    }

    void setIntensity(float intensity) override {

    }

    glm::vec3 getPosition() const override {
        return lightPosition;
    }
    glm::vec4 getColor() const override {
        return lightColor;
    }
    glm::vec3 getDirection() const {
        return direction;
    }
    float getIntensity() const override {
        return 0;
    }

    EventType getType() const override { return EventType::DirectionLight; }

private:
    glm::vec3 lightPosition;
    glm::vec4 lightColor;
    glm::vec3 direction;
};





