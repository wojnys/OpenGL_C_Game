#pragma once
#include "Scene.h"
#include "ModelManager.h"
#include "ShaderProgramManager.h"
#include "TextureManager.h"
#include "LightManager.h"
class TriangleScene : public Scene {
public:
    TriangleScene(GLFWwindow* window, Camera* camera, ShaderProgramManager* shaderProgramManager,
        TextureManager* textureManager, ModelManager* modelManager, LightManager* lightManager)
        : Scene(window, camera, shaderProgramManager, textureManager, modelManager, lightManager) {
        this->generateTriangleScene();
		printf("TriangleScene created\n");
    }

protected:
    void generateTriangleScene() {
        DrawableObject* loginModel = new DrawableObject(modelManager->getModelPair("login"), shaderProgramManager->getShaderProgram(9), textureManager->getTexture("wooden_fence"));
        loginModel->addTransformation(std::make_shared<Translate>(10.0f, 10.5f, 10.0f));
        loginModel->addTransformation(std::make_shared<Scale>(2, 2, 2));
        drawableObjects.push_back(loginModel);
   
       for (int i = 0; i < 10;i++) {
           DrawableObject* sph1 = new DrawableObject(modelManager->getModelPair("sphere"), shaderProgramManager->getShaderProgram(6), nullptr);
           sph1->addTransformation(std::make_shared<Translate>(10.0f + (i * 10), 9.5f, 10.0f));
   
           drawableObjects.push_back(sph1);
       }
   
       for (int i = 0; i < 10;i++) {
           DrawableObject* sph1 = new DrawableObject(modelManager->getModelPair("sphere"), shaderProgramManager->getShaderProgram(6), nullptr);
           sph1->addTransformation(std::make_shared<Translate>(10.0f, 9.5f, 10.0f + (i * 10)));
           drawableObjects.push_back(sph1);
       }
   
       DrawableObject* tr1 = new DrawableObject(modelManager->getModelPair("triangle"), shaderProgramManager->getShaderProgram(6), nullptr);
       tr1->addTransformation(std::make_shared<Translate>(8.0f, 7.5f, 12.0f));
       tr1->addTransformation(std::make_shared<Scale>(8.0f, 7.5f, 12.0f));
       drawableObjects.push_back(tr1);
   }
};


