#pragma once
#include "ShaderProgram.h"
#include "ShaderProgramFactory.h"

class ShaderProgramManager
{
public:
    ShaderProgram* createShaderProgram(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) {
        ShaderProgram* shaderprogram = ShaderProgramFactory::createShaderProgram(vertexPath, fragmentPath);
	    shaderPrograms.push_back(shaderprogram);

        return shaderprogram;
    }

    ShaderProgram* getShaderProgram(int indexInVector) const {
        if (indexInVector >= 0 && indexInVector < shaderPrograms.size()) {
            return shaderPrograms[indexInVector];
        }
        else {
            std::cerr << "Index out of bounds: " << indexInVector << std::endl;
            return nullptr;
        }
    }

    //void useShaderProgram(int indexInVector) {
    //    ShaderProgram* program = getShaderProgram(indexInVector);
    //    if (program) {
    //        program->useProgram();
    //    }
    //    else {
    //        std::cerr << "Shader program not found: " << indexInVector << std::endl;
    //    }
    //}

private:
    std::vector<ShaderProgram*> shaderPrograms;
};

