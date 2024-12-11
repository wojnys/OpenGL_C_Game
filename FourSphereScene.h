#pragma once
#include "Scene.h"
#include "ModelManager.h"
#include "ShaderProgramManager.h"
#include "TextureManager.h"
#include "GenerateRandomPosition.h"
#include "LightManager.h"
class FourSphereScene : public Scene {
public:
    FourSphereScene(GLFWwindow* window, Camera* camera, ShaderProgramManager* shaderProgramManager,
        TextureManager* textureManager, ModelManager* modelManager, LightManager* lightManager)
        : Scene(window, camera, shaderProgramManager, textureManager, modelManager, lightManager) {
        this->generateFourSphereScene();
        printf("Four sphere scene created\n");
    }

protected:
    void generateFourSphereScene() {
        DrawableObject* sph1 = new DrawableObject(modelManager->getModelPair("sphere"), shaderProgramManager->getShaderProgram(0), nullptr);
        sph1->addTransformation(std::make_shared<Translate>(-6.0f, 22.5f, 10.0f));
        drawableObjects.push_back(sph1);

        DrawableObject* sph2 = new DrawableObject(modelManager->getModelPair("sphere"), shaderProgramManager->getShaderProgram(0), nullptr);
        sph2->addTransformation(std::make_shared<Translate>(-3.5f, 20.0f, 10.0f));
        drawableObjects.push_back(sph2);

        DrawableObject* sph3 = new DrawableObject(modelManager->getModelPair("sphere"), shaderProgramManager->getShaderProgram(0), nullptr);
        sph3->addTransformation(std::make_shared<Translate>(-8.5f, 20.0f, 10.0f));
        drawableObjects.push_back(sph3);

        DrawableObject* sph4 = new DrawableObject(modelManager->getModelPair("sphere"), shaderProgramManager->getShaderProgram(0), nullptr);
        sph4->addTransformation(std::make_shared<Translate>(-6.0f, 17.5f, 10.0f));
    }
};

