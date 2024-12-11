#include "DrawableObject.h"
#include "BlenderModel.h"


// Constructor for Model -> because of LightDrawableObject
DrawableObject::DrawableObject(Model* model, ShaderProgram* shaderProgram)
    : type(ModelEnums::Model), shaderProgram(shaderProgram), model(model), texture(nullptr) {
    transformationGroup = new TransformationGroup();
}


DrawableObject::DrawableObject(std::pair<ModelBase*, ModelEnums> modelPair, ShaderProgram* shaderProgram, BaseTexture* texture)
    : modelBase(modelPair.first), type(modelPair.second), shaderProgram(shaderProgram), texture(texture) {
    transformationGroup = new TransformationGroup();
}

void DrawableObject::setNameOfObject(std::string name) {
    this->nameOfDrawableObject = name;
}
std::string DrawableObject::getNameOfObject() {
    return this->nameOfDrawableObject;

}

void DrawableObject::setObjectID(int objectID) {
	this->objectID = objectID;
}
int DrawableObject::getObjectID() {
	return this->objectID;
}

void DrawableObject::addTransformation(const std::shared_ptr<Transformation>& transformation) {
    transformationGroup->addTransformation(transformation);
}

void DrawableObject::clearAllTransformations() {
	transformationGroup->clearAllTransformations();
}

void DrawableObject::draw() {
    shaderProgram->useProgram();
    shaderProgram->makeTransformationForMultipleObjects(transformationGroup->getTransformedMatrix(glm::mat4(1.0f)));

    // Object (Model) identify
    glStencilFunc(GL_ALWAYS, objectID, 0xFF);

    switch (type) {
        case ModelEnums::Model: {
            Model* modelCasted = dynamic_cast<Model*>(modelBase);
            modelCasted->bind();
            glDrawArrays(modelCasted->getShapeType(), modelCasted->getFirst(), modelCasted->getCount());
			modelCasted->unbind();
            break;
        }

        case ModelEnums::TextureModel: {
            TextureModel* textureModelCasted = dynamic_cast<TextureModel*>(modelBase);
            textureModelCasted->bind();
            shaderProgram->setTexture(texture, texture->getTextureType());
            glDrawArrays(textureModelCasted->getShapeType(), textureModelCasted->getFirst(), textureModelCasted->getCount());
			textureModelCasted->unbind();
            break;
        }

        case ModelEnums::SkyCubeTextureModel: {
            SkyCubeTextureModel* skyCubeTextureModelCasted = dynamic_cast<SkyCubeTextureModel*>(modelBase);
            skyCubeTextureModelCasted->bind();
            shaderProgram->setTexture(texture, texture->getTextureType());
            glDrawArrays(skyCubeTextureModelCasted->getShapeType(), skyCubeTextureModelCasted->getFirst(), skyCubeTextureModelCasted->getCount());
			skyCubeTextureModelCasted->unbind();
            break;
        }

		case ModelEnums::BlenderModel: {
            BlenderModel* blenderModelCasted = dynamic_cast<BlenderModel*>(modelBase);
			blenderModelCasted->bind();
            shaderProgram->setTexture(texture, texture->getTextureType());
            glDrawElements(GL_TRIANGLES, blenderModelCasted->getIndiciesCount(), GL_UNSIGNED_INT, NULL);
            blenderModelCasted->unbind();
			break;
		}
    }
}
