#include "SceneFactory.h"
#include "ShaderProgramManager.h"
#include "TriangleScene.h"
#include "ForestScene.h"
#include "ReflectorScene.h"
#include "FourSphereScene.h"
#include "DifferentSpheres.h"
#include "LightForestScene.h"
#include "SkyCubeScene.h"

std::shared_ptr<Scene> SceneFactory::createScene(int type, GLFWwindow* window, Camera* camera, ShaderProgramManager* shaderProgramManager, TextureManager* textureManager, ModelManager* modelManager, LightManager* lightManager) {
    switch (type) {
    case 0:
        return std::make_shared<SkyCubeScene>(window, camera, shaderProgramManager, textureManager, modelManager, lightManager);
        break;
    case 1:
        return std::make_shared<TriangleScene>(window, camera, shaderProgramManager, textureManager, modelManager, lightManager);
        break;
    case 2:  
        return std::make_shared<ForestScene>(window, camera, shaderProgramManager, textureManager, modelManager, lightManager);
        break;
    case 3:
        return std::make_shared<ReflectorScene>(window, camera, shaderProgramManager, textureManager, modelManager, lightManager);
        break;
    case 4:
        return std::make_shared<LightForestScene>(window, camera, shaderProgramManager, textureManager, modelManager, lightManager);
        break;
    case 5:
        return std::make_shared<FourSphereScene>(window, camera, shaderProgramManager, textureManager, modelManager, lightManager);
        break;  
    case 6:
        return std::make_shared<DifferentSpheres>(window, camera, shaderProgramManager, textureManager, modelManager, lightManager);
        break;

    default:  
        return nullptr;
        break;
    }
    return nullptr;
}
