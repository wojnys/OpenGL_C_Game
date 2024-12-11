#pragma once
#include "Scene.h"
#include "ModelManager.h"
#include "ShaderProgramManager.h"
#include "TextureManager.h"
#include "LightManager.h"
#include "GenerateRandomPosition.h"
#include "BezierData.h"

class ForestScene : public Scene {
public:
    ForestScene(GLFWwindow* window, Camera* camera, ShaderProgramManager* shaderProgramManager,
        TextureManager* textureManager, ModelManager* modelManager, LightManager* lightManager)
        : Scene(window, camera, shaderProgramManager, textureManager, modelManager, lightManager) {
        this->generateForestScene();
        printf("Forest scene created\n");
    }

protected:
    void generateForestScene() {
            GenerateRandomPosition generateRandomPosition;
       
           for (int i = 0; i < 50; i++) {
               float randX = generateRandomPosition.generateRandomFloatNumber(-30.0f, 30.0f);
               float randZ = generateRandomPosition.generateRandomFloatNumber(-30.0f, 30.0f);
       
               DrawableObject* tree = new DrawableObject(modelManager->getModelPair("tree_blender"), shaderProgramManager->getShaderProgram(7), textureManager->getTexture("tree"));
               tree->addTransformation(std::make_shared<Translate>(randX, 1.0f, randZ));
               tree->addTransformation(std::make_shared<Scale>(0.2f, 0.2f, 0.2f));
               if (i % 2 == 0) {
                   tree->addTransformation(std::make_shared<DynamicRotate>(1.0f, 0.0f, 1.0f, 0.0f));
               }
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
       
           DrawableObject* platformDr = new DrawableObject(modelManager->getModelPair("teren_blender"), shaderProgramManager->getShaderProgram(9), textureManager->getTexture("grass"));
           platformDr->addTransformation(std::make_shared<Translate>(1.0f, 1.0f, 1.0f));
           //platformDr->addTransformation(std::make_shared<Scale>(60.f, 30.7f, 60.7f));
           drawableObjects.push_back(platformDr);


           DrawableObject* houseModel1 = new DrawableObject(modelManager->getModelPair("house_blender_model"), shaderProgramManager->getShaderProgram(9), textureManager->getTexture("house"));
           houseModel1->addTransformation(std::make_shared<Translate>(1.0f, 1, 1.0f));
           houseModel1->addTransformation(std::make_shared<Scale>(2, 2, 2));
           drawableObjects.push_back(houseModel1);

           DrawableObject* zombieBezineCurve = new DrawableObject(modelManager->getModelPair("zombie"), shaderProgramManager->getShaderProgram(9), textureManager->getTexture("zombie"));
           zombieBezineCurve->addTransformation(std::make_shared<Scale>(10.0f, 10.0f, 10.0f));
           zombieBezineCurve->addTransformation(std::make_shared<BezinCurve>(A, B, 0.5, 0.1));
           drawableObjects.push_back(zombieBezineCurve);

           glm::vec3 positionOffset(20.0f, 1.0f, 20.0f);
           glm::vec3 positionOffset1(-20.0f, 1.0f, 20.0f);
      
            DrawableObject* zombieBezineCurve1 = new DrawableObject(modelManager->getModelPair("zombie"), shaderProgramManager->getShaderProgram(9), textureManager->getTexture("zombie"));
            zombieBezineCurve1->addTransformation(std::make_shared<BezinCurve>(A, B, 0.5, 0.05, positionOffset));
            zombieBezineCurve1->addTransformation(std::make_shared<Scale>(5.0f, 5.0f, 5.0f));
            drawableObjects.push_back(zombieBezineCurve1);

            DrawableObject* zombieBezineCurve2 = new DrawableObject(modelManager->getModelPair("zombie"), shaderProgramManager->getShaderProgram(9), textureManager->getTexture("zombie"));
            zombieBezineCurve2->addTransformation(std::make_shared<BezinCurve>(A, B, 0.5, 0.3, positionOffset1));
            zombieBezineCurve2->addTransformation(std::make_shared<Scale>(5.0f, 5.0f, 5.0f));
            drawableObjects.push_back(zombieBezineCurve2);

           DrawableObject* loginModel = new DrawableObject(modelManager->getModelPair("login"), shaderProgramManager->getShaderProgram(9), textureManager->getTexture("grass"));
           loginModel->addTransformation(std::make_shared<Translate>(-6.0f, 30, 1.0f));
           loginModel->addTransformation(std::make_shared<Scale>(4, 4, 4));
           drawableObjects.push_back(loginModel);

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
           drawableObjects.push_back(sph4);
       }
};