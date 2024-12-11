#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager() {
}

void SceneManager::addScene(std::shared_ptr<Scene> scene) {
    scenes.push_back(scene);
}

void SceneManager::switchToScene(int index) {
    if (index >= 0 && index < scenes.size()) {
        currentSceneIndex = index;
    }
}

void SceneManager::renderCurrentScene() {
    if (!scenes.empty()) {
        scenes[currentSceneIndex]->render();
    }
}

int SceneManager::getSceneCount() {
    return scenes.size();
}

void SceneManager::clear() {

    for (auto& sceneEl : scenes) {
        sceneEl->clear();
    }

}

void SceneManager::renderSkyCubeScene() {
    scenes[0]->render();
}

