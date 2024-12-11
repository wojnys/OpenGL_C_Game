#pragma once

#include <iostream>
#include <string>


#include <GL/glew.h>
#include <SOIL.h>
#include "TextureBase.h"


// priradim do drawableObjectu - agregace - pouze pokud ma jeden material, jeden model, jednu texturu ->

class Texture : public BaseTexture {
private:
    std::string filePath;

public:
    Texture(const char* texturePath, int textureUnitNumber) : filePath(texturePath) {
         this->textureUnitNumber = textureUnitNumber;
        //Texture one in texture unit 1,2,3,4,5...
        glActiveTexture(GL_TEXTURE0 + this->textureUnitNumber);
        textureID = SOIL_load_OGL_texture(texturePath, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
        if (textureID == NULL) {
            std::cout << "An error occurred while loading texture." << std::endl;
            exit(EXIT_FAILURE);
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glBindTexture(GL_TEXTURE_2D, textureID);

    }

    TextureEnums getTextureType() const override {
        return TextureEnums::Texture;
    }

    int getTextureNumberUnit() const {
         return textureUnitNumber;
     }
};



