#pragma once
#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "Models.h"
#include "ShaderProgram.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>
#include "Transformation.h"
#include "TextureModel.h"
#include "SkyCubeTextureModel.h"
#include "ModelEnums.h"
#include "TextureBase.h"
#include "ModelBase.h"

class DrawableObject {
public:

    DrawableObject(Model* model, ShaderProgram* shaderProgram);

    DrawableObject(std::pair<ModelBase*, ModelEnums> modelPair, ShaderProgram* shaderProgram, BaseTexture* texture);

    void addTransformation(const std::shared_ptr<Transformation>& transformation);
    void applyTransformations(glm::mat4& modelMatrix);
    void clearAllTransformations();

    void setNameOfObject(std::string name);
    std::string getNameOfObject();

    void draw();
    void drawTextureModel();
    void setObjectID(int objectID); // For stelcil identification
    int getObjectID();

protected:
    
    ShaderProgram* shaderProgram;
    TransformationGroup* transformationGroup;
	BaseTexture* texture;
	ModelBase* modelBase;

    Model* model;
    TextureModel* textureModel;

    std::string nameOfDrawableObject;

    ModelEnums type;
    int objectID;
};

#endif 

