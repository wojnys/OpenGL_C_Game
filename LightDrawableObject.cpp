#include "LightDrawableObject.h"
#include <cstdlib>
#include <ctime>
#include <glm/gtc/random.hpp>

LightDrawableObject::LightDrawableObject(Model* model, ShaderProgram* shaderProgram)
    : DrawableObject(model, shaderProgram) {

}

LightDrawableObject::LightDrawableObject(std::pair<ModelBase*, ModelEnums> modelPair, ShaderProgram* shaderProgram, BaseTexture* texture)
    : DrawableObject(modelPair, shaderProgram, texture) {
    //transformationGroup = new TransformationGroup();
}

void LightDrawableObject::setPosition(const glm::vec3& position) {
    this->position = position;
}

void LightDrawableObject::setColor(const glm::vec4& color) {
    this->color = color;
}

glm::vec3 LightDrawableObject::getPosition() const {
    return position;
}

glm::vec4 LightDrawableObject::getColor() const {
    return color;
}

void LightDrawableObject::updatePosition(const glm::vec3& deltaPosition) {
    position += deltaPosition;
    addTransformation(std::make_shared<Translate>(position.x, position.y, position.z));
    if (position.x >= 50.0 || position.x <= -50.0 || position.z >= 50.0 || position.z <= -50.0)
        position.x = 0;

    setPosition(position);
    //applyTransformations();
}
