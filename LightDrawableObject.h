#pragma once
#include "DrawableObject.h"
#include "Light.h"
#include <glm/glm.hpp>


class LightDrawableObject : public DrawableObject, public Light {
public:
    LightDrawableObject(Model* model, ShaderProgram* shaderProgram);

    LightDrawableObject(std::pair<ModelBase*, ModelEnums> modelPair, ShaderProgram* shaderProgram, BaseTexture* texture);

    void setPosition(const glm::vec3& position);
    void setColor(const glm::vec4& color);
    glm::vec3 getPosition() const;
    glm::vec4 getColor() const;
    void updatePosition(const glm::vec3& deltaPosition);

private:
    glm::vec3 position;
    glm::vec4 color;
    glm::vec3 velocity;

    ShaderProgram* shaderProgram;
    BaseTexture* texture;
    ModelBase* modelBase;

    ModelEnums type;
};


