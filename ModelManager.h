#pragma once

#include "Models.h"
#include "TextureModel.h"
#include "SkyCubeTextureModel.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include "ModelBase.h"
#include "BlenderModel.h"
#include "ModelEnums.h"

class ModelManager {
private:
    // Map storing both ModelBase* and ModelEnums type
    std::unordered_map<std::string, std::pair<ModelBase*, ModelEnums>> modelMap;

public:
    ModelManager() {}

    ~ModelManager() {
        for (auto& modelPair : modelMap) {
            delete modelPair.second.first;
        }
    }

    ModelBase* loadModel(const std::string modelName, const float points[], size_t size, GLenum shapeType, int first, int count, ModelEnums modelType) {
        if (modelMap.find(modelName) != modelMap.end()) {
            std::cout << "Model \"" << modelName << "\" already loaded." << std::endl;
            return modelMap[modelName].first;
        }

        ModelBase* newModel = nullptr;

        if (modelType == ModelEnums::Model) {
            newModel = new Model(points, size, shapeType, first, count);
            std::cout << "Loaded model: " << modelName << std::endl;
        }
        else if (modelType == ModelEnums::TextureModel) {
            newModel = new TextureModel(points, size, shapeType, first, count);
            std::cout << "Loaded texture model: " << modelName << std::endl;
        }
        else if (modelType == ModelEnums::SkyCubeTextureModel) {
            newModel = new SkyCubeTextureModel(points, size, shapeType, first, count);
            std::cout << "Loaded sky cube texture model: " << modelName << std::endl;
        }
        else {
            std::cerr << "Error: Unknown model type." << std::endl;
            return nullptr;
        }

        // Store the model and its type in the map
        modelMap[modelName] = { newModel, modelType };
        return newModel;
    }

    ModelBase* loadBlenderModel(const std::string modelName, const std::string modelFulName, ModelEnums modelType) {
        if (modelMap.find(modelName) != modelMap.end()) {
            std::cout << "Model \"" << modelName << "\" already loaded." << std::endl;
            return modelMap[modelName].first;
        }

        ModelBase* newModel = nullptr;
        if (modelType == ModelEnums::BlenderModel) {
            newModel = new BlenderModel(modelFulName);
            std::cout << "Loaded blender model: " << modelFulName << std::endl;
        }
        else {
            std::cerr << "Error: Unknown model type." << std::endl;
            return nullptr;
        }

        // Store the model and its type in the map
        modelMap[modelName] = { newModel, modelType };
        return newModel;
    }


    // Returns both the ModelBase* and its ModelEnums type
    std::pair<ModelBase*, ModelEnums> getModelPair(const std::string& modelName) const {
        auto it = modelMap.find(modelName);
        if (it == modelMap.end()) {
            std::cerr << "Error: Model \"" << modelName << "\" not found." << std::endl;
            exit(0);
            return { nullptr, ModelEnums::Model };
        }
        return {it->second.first, it->second.second}; 
    }

    // Returns only the ModelBase*
    ModelBase* getModel(const std::string& modelName) const {
        auto it = modelMap.find(modelName);
        if (it == modelMap.end()) {
            std::cerr << "Error: Model \"" << modelName << "\" not found." << std::endl;
            return nullptr;
        }
        return it->second.first; // Return the ModelBase* only
    }

    void bindModel(const std::string& modelName) const {
        ModelBase* model = getModel(modelName);
        if (model) {
            model->bind();
        }
    }

    void unbindModel(const std::string& modelName) const {
        ModelBase* model = getModel(modelName);
        if (model) {
            model->unbind();
        }
    }
};
