#pragma once

#include <memory>
#include "Scene.h"
#include "ShaderProgram.h"
#include "ShaderProgramManager.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "LightManager.h"

class SceneFactory {
public:
    static std::shared_ptr<Scene> createScene(int type, GLFWwindow* window, Camera* camera, ShaderProgramManager* shaderProgramManager, TextureManager* textureManager, ModelManager* modelManager, LightManager* lightManager);
};


