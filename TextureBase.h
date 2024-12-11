#pragma once

#include <GL/glew.h>
#include <string>

enum class TextureEnums {
    Texture,
    CubeMapTexture
};

class BaseTexture {
protected:
    GLuint textureID;
    int textureUnitNumber;

public:
    BaseTexture() : textureID(0), textureUnitNumber(0) {}
    virtual ~BaseTexture() { glDeleteTextures(1, &textureID); }

    virtual TextureEnums getTextureType() const = 0;
    virtual int getTextureNumberUnit() const = 0;
};


