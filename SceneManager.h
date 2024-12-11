#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "ShaderProgram.h"
class Scene;

class SceneManager {
public:
    SceneManager();

    void addScene(std::shared_ptr<Scene> scene);
    void switchToScene(int index);
    void renderCurrentScene();
    void renderSkyCubeScene();
    int getSceneCount();
    void clear();

private:
    std::vector<std::shared_ptr<Scene>> scenes;
    int currentSceneIndex = 0;
};



