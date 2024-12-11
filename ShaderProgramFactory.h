#pragma once
#ifndef SHADER_FACTORY_H
#define SHADER_FACTORY_H

#include "ShaderProgram.h"
#include <string>

class ShaderProgramFactory {
public:
    static ShaderProgram* createShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) {
        ShaderLoader loader;
        GLuint shaderID = loader.loadShader(vertexPath.c_str(), fragmentPath.c_str());
        return new ShaderProgram(shaderID);
    }
};

#endif 

