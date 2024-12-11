#pragma once
#include "Scene.h"
#include "ModelManager.h"
#include "ShaderProgramManager.h"
#include "TextureManager.h"
#include "GenerateRandomPosition.h"
#include "BezierData.h"

class LightForestScene : public Scene {
public:
    LightForestScene(GLFWwindow* window, Camera* camera, ShaderProgramManager* shaderProgramManager,
        TextureManager* textureManager, ModelManager* modelManager, LightManager* lightManager)
        : Scene(window, camera, shaderProgramManager, textureManager, modelManager, lightManager) {
        this->generateForestScene();
        printf("Light Forest scene created\n");
    }

protected:
    void generateForestScene() {
        GenerateRandomPosition generateRandomPosition;

        for (int i = 0; i < 100; i++) {
            float randX = generateRandomPosition.generateRandomFloatNumber(-30.0f, 30.0f);
            float randZ = generateRandomPosition.generateRandomFloatNumber(-30.0f, 30.0f);

            DrawableObject* tree = new DrawableObject(modelManager->getModelPair("tree"), shaderProgramManager->getShaderProgram(4), nullptr);
            tree->addTransformation(std::make_shared<Translate>(randX, 1.0f, randZ));
            tree->addTransformation(std::make_shared<Scale>(0.9f, 0.9f, 1.0f));

            tree->addTransformation(std::make_shared<DynamicRotate>(1.0f, 0.0f, 1.0f, 0.0f));
            
            drawableObjects.push_back(tree);
        }

        for (int i = 0; i < 40; i++) {
            float randX = generateRandomPosition.generateRandomFloatNumber(-20.0f, 20.0f);
            float randZ = generateRandomPosition.generateRandomFloatNumber(-20.0f, 20.0f);

            DrawableObject* bush = new DrawableObject(modelManager->getModelPair("bushes"), shaderProgramManager->getShaderProgram(4), nullptr);
            bush->addTransformation(std::make_shared<Translate>(randX, 1.0f, randZ));
            bush->addTransformation(std::make_shared<Scale>(2.7f, 2.7f, 2.7f));
            drawableObjects.push_back(bush);
        }

        DrawableObject* platformDr = new DrawableObject(modelManager->getModelPair("plain"), shaderProgramManager->getShaderProgram(4), nullptr);
        platformDr->addTransformation(std::make_shared<Translate>(1.0f, 1.0f, 1.0f));
        platformDr->addTransformation(std::make_shared<Scale>(300.f, 30.7f, 300.7f));
        drawableObjects.push_back(platformDr);
    }
};

