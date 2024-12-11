#pragma once
#include <iostream>
#include <string>


#include <GL/glew.h>
#include <SOIL.h>
#include "TextureBase.h"

class CubeMapTexture : public BaseTexture {
private:
    std::string filePaths[6];

public:
    CubeMapTexture(const char* paths[6], int textureUnitNumber) {
        this->textureUnitNumber = textureUnitNumber;

        glActiveTexture(GL_TEXTURE0 + this->textureUnitNumber);
        textureID = SOIL_load_OGL_cubemap(paths[0], paths[1], paths[2], paths[3], paths[4], paths[5],SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
        if (textureID == NULL) {
            std::cout << "An error occurred while loading CubeMap." << std::endl;
            exit(EXIT_FAILURE);
        }

        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    }

    TextureEnums getTextureType() const override {
        return TextureEnums::CubeMapTexture;
    }

    int getTextureNumberUnit() const {
        return textureUnitNumber;
    }
};


