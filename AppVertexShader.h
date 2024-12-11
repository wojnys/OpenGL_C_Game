// trida bude dedit z SHADER

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"

#pragma once

class AppVertexShader : public Shader{
public:
	AppVertexShader(const char* source);
	GLuint getVertexShaderID() const;

private:
	GLuint vertexShaderID;

};

