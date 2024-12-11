#pragma once
#include <vector>
#include <memory>
#include "LightInterface.h"
#include "Subject.h"
#include "SpotLight.h"

class LightManager : public Subject {
private:
    std::vector<LightInterface*> lights;
    std::vector<LightInterface*> tmpLights;

public:
    void addLight(LightInterface* light) {
        lights.push_back(light);
        notify(EventType::Light, light);
    }

    void updateLights() {
        for (auto& light : lights) {
            EventType type = light->getType();
            this->notify(type, light);
        }
    }

    void editSpotLight(glm::vec3 position, glm::vec3 direction, glm::vec4 color) {
        // Find the last SpotLight in the vector
        SpotLight* sp = dynamic_cast<SpotLight*>(lights.back());
        sp->setColor(color);
        sp->setPosition(position);
        sp->setDirection(direction);

        for (auto& light : lights) {
            if (light->getType() == EventType::SpotLight) {
                SpotLight* sp = dynamic_cast<SpotLight*>(lights.back());
                cout << sp->getDirection().x << " " << sp->getDirection().y << " " << sp->getDirection().z << endl;
                cout << sp->getPosition().x << " " << sp->getPosition().y << " " << sp->getPosition().z << endl;
            }
        }
    }

    void editLight(int index, glm::vec3 position, glm::vec4 color) {
        lights[index]->setPosition(position);
        lights[index]->setColor(color);
    }



    void removeLight(int index) {
        lights.erase(lights.begin() + index);
    }

    const std::vector<LightInterface*>& getLights(EventType type) const {
        static std::vector<LightInterface*> tmpLights;
        tmpLights.clear();

        if (type == EventType::None) {
            return lights;
        }
        for (auto& light : lights) {
            if (light->getType() == type) {
                tmpLights.push_back(light);
            }
        }

        return tmpLights;
    }
};
