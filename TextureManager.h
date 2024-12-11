#pragma once

#include "Texture.h"
#include "TextureCubeMap.h"
#include <unordered_map>
#include <string>
#include <iostream>


class TextureManager {
private:
    std::unordered_map<std::string, BaseTexture*> textureMap;
    int textureUnit = -1;

public:
    TextureManager() {}

    ~TextureManager() {
        for (auto& texturePair : textureMap) {
            delete texturePair.second;
        }
    }

    BaseTexture* loadTexture2D(const std::string& textureName, const char* filePath) {
        // prvni hodnata bude 0
        textureUnit += 1;

        if (textureMap.find(textureName) != textureMap.end()) {
            std::cout << "Texture \"" << textureName << "\" already loaded." << std::endl;
            return textureMap[textureName];
        }

        Texture* newTexture = new Texture(filePath, textureUnit);
        textureMap[textureName] = newTexture;
        std::cout << "Loaded 2D texture: " << textureName << " from file: " << filePath << std::endl;
        return newTexture;
    }

    BaseTexture* loadCubeMap(const std::string& textureName, const char* filePaths[6]) {
        textureUnit += 1;
        if (textureMap.find(textureName) != textureMap.end()) {
            std::cout << "Cube map \"" << textureName << "\" already loaded." << std::endl;
            return textureMap[textureName];
        }

        CubeMapTexture* newCubeMap = new CubeMapTexture(filePaths, textureUnit);
        textureMap[textureName] = newCubeMap;
        std::cout << "Loaded cube map: " << textureName << std::endl;
        return newCubeMap;
    }

    BaseTexture* getTexture(const std::string& textureName) {
        if (textureMap.find(textureName) == textureMap.end()) {
            std::cerr << "Error: Texture \"" << textureName << "\" not found." << std::endl;
            return nullptr;
        }
        return textureMap[textureName];
    }

    //void bindTexture(const std::string& textureName) {
    //    BaseTexture* texture = getTexture(textureName);
    //    if (texture) {
    //        texture->bind();
    //    }
    //}

    //void unbindTexture(const std::string& textureName) {
    //    BaseTexture* texture = getTexture(textureName);
    //    if (texture) {
    //        texture->unbind();
    //    }
    //}
};

