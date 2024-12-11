#pragma once
#pragma once
#include "Scene.h"
#include "ModelManager.h"
#include "ShaderProgramManager.h"
#include "TextureManager.h"
#include "GenerateRandomPosition.h"
#include "LightManager.h"
class ReflectorScene : public Scene {
public:
    ReflectorScene(GLFWwindow* window, Camera* camera, ShaderProgramManager* shaderProgramManager,
        TextureManager* textureManager, ModelManager* modelManager, LightManager* lightManager)
        : Scene(window, camera, shaderProgramManager, textureManager, modelManager, lightManager) {
        this->generateReflectorScene();
        printf("ReflectorScene scene created\n");
    }

protected:
    void generateReflectorScene() {
        GenerateRandomPosition generateRandomPosition;
        for (int i = 0; i < 75; i++) {
            float randX = generateRandomPosition.generateRandomFloatNumber(-50.0f, 50.0f);
            float randY = generateRandomPosition.generateRandomFloatNumber(-50.0f, 40.0f);
            float randZ = generateRandomPosition.generateRandomFloatNumber(-40.0f, 40.0f);
        
            DrawableObject* tree = new DrawableObject(modelManager->getModelPair("tree"), shaderProgramManager->getShaderProgram(5), nullptr);
        
            tree->addTransformation(std::make_shared<Translate>(randX, 1.0f, randZ));
        
            int randomRotateAngle = generateRandomPosition.generateRandomFloatNumber(-30.0f, 30.0f);
            tree->addTransformation(std::make_shared<Scale>(0.9f, 0.9f, 1.0f));
            tree->addTransformation(std::make_shared<Rotate>(randomRotateAngle, 0.0f, 1.0f, 0.0f));
        
            if (i % 2 == 0) {
                tree->addTransformation(std::make_shared<DynamicTranslate>(randX, 1.0f, randZ, randX + 40.0f, 5.0f, randZ + .0f, 0.02f));
                tree->addTransformation(std::make_shared<DynamicRotate>(1.0f, 0.0f, 1.0f, 0.0f));
            }
        
            drawableObjects.push_back(tree);
        }
        for (int i = 0; i < 80; i++) {
            float randX = generateRandomPosition.generateRandomFloatNumber(-40.0f, 40.0f);
            float randY = generateRandomPosition.generateRandomFloatNumber(-40.0f, 40.0f);
            float randZ = generateRandomPosition.generateRandomFloatNumber(-40.0f, 40.0f);
        
            DrawableObject* bush = new DrawableObject(modelManager->getModelPair("bushes"), shaderProgramManager->getShaderProgram(5), nullptr);
            bush->addTransformation(std::make_shared<Translate>(randX, 1.0f, randZ));
            drawableObjects.push_back(bush);
        }
        
        DrawableObject* platformDr = new DrawableObject(modelManager->getModelPair("plain"), shaderProgramManager->getShaderProgram(5), nullptr);
        platformDr->addTransformation(std::make_shared<Translate>(1.0f, 1.0f, 1.0f));
        platformDr->addTransformation(std::make_shared<Scale>(200.f, 50.7f, 200.7f));
        drawableObjects.push_back(platformDr);
    }
};
