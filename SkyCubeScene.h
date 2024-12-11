#pragma once
#include "Scene.h"
#include "ModelManager.h"
#include "ShaderProgramManager.h"
#include "TextureManager.h"
#include "GenerateRandomPosition.h"
#include "LightManager.h"
class SkyCubeScene : public Scene {
public:
    SkyCubeScene(GLFWwindow* window, Camera* camera, ShaderProgramManager* shaderProgramManager,
        TextureManager* textureManager, ModelManager* modelManager, LightManager* lightManager)
        : Scene(window, camera, shaderProgramManager, textureManager, modelManager, lightManager) {
        this->generateSkyCubeScene();
        printf("SkyCube scene created\n");
    }

protected:
    void generateSkyCubeScene() {
        DrawableObject* skCube1 = new DrawableObject(modelManager->getModelPair("skycube"), shaderProgramManager->getShaderProgram(8), textureManager->getTexture("skycube"));
        skCube1->addTransformation(std::make_shared<Translate>(10.0f, 10.5f, -10.0f));
        skCube1->addTransformation(std::make_shared<Scale>(20.0f,20.f, 20.0f));
		skCube1->setNameOfObject("skycubeBackground");

        drawableObjects.push_back(skCube1);
    }

private:
    DrawableObject* skCube1;
};